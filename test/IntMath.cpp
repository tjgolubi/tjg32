#include "tjg/IntMath.hpp"
#include "crc/CrcKnown.hpp"

#include <random>
#include <type_traits>
#include <typeinfo>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <cstddef>
#include <cstdlib>
#include <cxxabi.h>

namespace IntMath2 {

/// The number of set bits.
template<std::unsigned_integral T>
[[deprecated("use std::popcount() instead")]]
constexpr int NumOnes(T x) noexcept { return std::popcount(x); }

/// Bit position of the right-most-one, the least-significant set bit.
template<std::unsigned_integral T>
constexpr int lmo(T x) noexcept { return std::bit_width(x) - 1; }

/// Bit position of the right-most-one, the least-significant set bit.
template<std::unsigned_integral T>
constexpr int rmo(T x) noexcept
{ return (x == T{0}) ? -1 : std::countr_zero(x); }

/// Value of the right-most-one, the least-significant set bit.
template<std::unsigned_integral T>
constexpr T rmb(T x) noexcept
{ return (x == T{0}) ? T{0} : (T{1} << std::countr_zero(x)); }

/// Value of the left-most-one, the most-significant set bit.
template<std::unsigned_integral T>
constexpr T lmb(T x) noexcept { return std::bit_floor(x); }

} // IntMath2

#define OP lmb

template<typename T>
requires (!std::integral<T>)
std::string TypeName() noexcept {
  int status = 0;
  char* demangled = abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, &status);
  std::string result = (status == 0 && demangled) ? demangled : typeid(T).name();
  std::free(demangled);
  return result;
} // TypeName

template<std::integral T>
std::string TypeName() noexcept {
  std::string s;
  s.reserve(8);
  if constexpr (std::is_unsigned_v<T>)
    s += 'u';
  s += "int" + std::to_string(8 * sizeof(T)) + "_t";
  return s;
}

constexpr auto LoopCount = 100 * (1 << 20);
constexpr auto Seed = 12345;

template<std::integral U>
using Rng = std::conditional_t<sizeof(U)<=sizeof(std::uint32_t),
                                 std::mt19937, std::mt19937_64>;

template<std::unsigned_integral U>
bool Test() {
  auto rng = Rng<U>{};
  rng.seed(Seed);
  for (int i = LoopCount; i--; ) {
    auto x = static_cast<U>(rng());
    if (tjg::IntMath::OP(x) != IntMath2::OP(x))
      return false;
  }
  return true;
} // Test

using Crc = tjg::crc::FastCrc32;

using Clock = std::chrono::high_resolution_clock;
struct TimedResult {
  std::chrono::milliseconds elapsed;
  Crc::value_type crc;
  constexpr TimedResult(auto dt, Crc::value_type crc_) noexcept
    : elapsed{std::chrono::duration_cast<std::chrono::milliseconds>(dt)}
    , crc{crc_}
    { }
}; // TimedResult

template<std::unsigned_integral U>
auto TimedTest1() {
  auto rng = Rng<U>{};
  rng.seed(Seed);
  auto result = Crc{};
  auto start = Clock::now();
  for (auto i = LoopCount; i--; ) {
    auto x = tjg::IntMath::OP(static_cast<U>(rng()));
    result.update(static_cast<std::byte>(x));
  }
  auto stop = Clock::now();
  return TimedResult{stop-start, result.value()};
} // TimedTest1

template<std::unsigned_integral U>
auto TimedTest2() {
  auto rng = Rng<U>{};
  rng.seed(Seed);
  auto result = Crc{};
  auto start = Clock::now();
  for (auto i = LoopCount; i--; ) {
    auto x = IntMath2::OP(static_cast<U>(rng()));
    result.update(static_cast<std::byte>(x));
  }
  auto stop = Clock::now();
  return TimedResult{stop-start, result.value()};
} // TimedTest2

template<std::unsigned_integral U>
bool TimedTest() {
  auto result1 = TimedTest1<U>();
  auto result2 = TimedTest2<U>();
  {
    using namespace std;
    cout << setw(8) << TypeName<U>() << '\t';
    cout << result1.elapsed << '\t' << result2.elapsed;
  }
  bool result = (result1.crc == result2.crc);
  if (!result)
    std::cout << " WRONG!";
  std::cout << '\n';
  return result;
} // TimedTest

int main() {
  using namespace std;

  int failCount = 0;
  failCount += !Test<std::uint8_t >();
  failCount += !Test<std::uint16_t>();
  failCount += !Test<std::uint32_t>();
  failCount += !Test<std::uint64_t>();

  std::cout << "Type    \tOld\tNew\n";
  failCount += !TimedTest<std::uint8_t >();
  failCount += !TimedTest<std::uint16_t>();
  failCount += !TimedTest<std::uint32_t>();
  failCount += !TimedTest<std::uint64_t>();

  if (failCount > 0) {
    std::cout << "Failed " << failCount << "/8 tests." << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
} // main

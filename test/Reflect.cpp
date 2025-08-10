#include "tjg/Reflect.hpp"

#include <random>
#include <type_traits>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <cstddef>
#include <cstdlib>
#include <cxxabi.h>

namespace IntMath {

constexpr std::uint8_t Reflect(std::uint8_t x) noexcept {
  x = ((x & 0x55) << 1) | ((x & 0xaa) >> 1);
  x = ((x & 0x33) << 2) | ((x & 0xcc) >> 2);
  x = ((x & 0x0f) << 4) | ((x & 0xf0) >> 4);
  return x;
} // Reflect

constexpr std::byte Reflect(std::byte x) noexcept {
  return std::byte{Reflect(std::to_integer<std::uint8_t>(x))};
}

constexpr std::uint16_t Reflect(std::uint16_t x) noexcept {
  x = ((x & 0x5555) << 1) | ((x & 0xaaaa) >> 1);
  x = ((x & 0x3333) << 2) | ((x & 0xcccc) >> 2);
  x = ((x & 0x0f0f) << 4) | ((x & 0xf0f0) >> 4);
  x = ((x & 0x00ff) << 8) | ((x & 0xff00) >> 8);
  return x;
} // Reflect

constexpr std::uint32_t Reflect(std::uint32_t x) noexcept {
  x = ((x & 0x55555555) << 1) | ((x & 0xaaaaaaaa) >> 1);
  x = ((x & 0x33333333) << 2) | ((x & 0xcccccccc) >> 2);
  x = ((x & 0x0f0f0f0f) << 4) | ((x & 0xf0f0f0f0) >> 4);
  x = ((x & 0x00ff00ff) << 8) | ((x & 0xff00ff00) >> 8);
  x = ((x & 0x0000ffff) <<16) | ((x & 0xffff0000) >>16);
  return x;
} // Reflect

constexpr std::uint64_t Reflect(std::uint64_t x) noexcept {
  x = ((x & 0x5555555555555555) << 1) | ((x & 0xaaaaaaaaaaaaaaaa) >> 1);
  x = ((x & 0x3333333333333333) << 2) | ((x & 0xcccccccccccccccc) >> 2);
  x = ((x & 0x0f0f0f0f0f0f0f0f) << 4) | ((x & 0xf0f0f0f0f0f0f0f0) >> 4);
  x = ((x & 0x00ff00ff00ff00ff) << 8) | ((x & 0xff00ff00ff00ff00) >> 8);
  x = ((x & 0x0000ffff0000ffff) <<16) | ((x & 0xffff0000ffff0000) >>16);
  x = ((x & 0x00000000ffffffff) <<32) | ((x & 0xffffffff00000000) >>32);
  return x;
} // Reflect

} // IntMath

static_assert(IntMath::Reflect(std::byte{0x00}) == std::byte{0x00});
static_assert(IntMath::Reflect(std::byte{0xff}) == std::byte{0xff});
static_assert(IntMath::Reflect(std::byte{0xa5}) == std::byte{0xa5});
static_assert(IntMath::Reflect(std::byte{0x5a}) == std::byte{0x5a});
static_assert(IntMath::Reflect(std::byte{0xca}) == std::byte{0x53});
static_assert(IntMath::Reflect(std::byte{0x53}) == std::byte{0xca});
static_assert(IntMath::Reflect(std::byte{0x80}) == std::byte{0x01});

static_assert(IntMath::Reflect(std::uint16_t{0x0000}) == std::uint16_t{0x0000});
static_assert(IntMath::Reflect(std::uint16_t{0xffff}) == std::uint16_t{0xffff});
static_assert(IntMath::Reflect(std::uint16_t{0xa5ca}) == std::uint16_t{0x53a5});
static_assert(IntMath::Reflect(std::uint16_t{0x8001}) == std::uint16_t{0x8001});
static_assert(IntMath::Reflect(std::uint16_t{0x0cba}) == std::uint16_t{0x5d30});
static_assert(IntMath::Reflect(std::uint16_t{0x4079}) == std::uint16_t{0x9e02});
static_assert(IntMath::Reflect(std::uint16_t{0x08fd}) == std::uint16_t{0xbf10});
static_assert(IntMath::Reflect(std::uint16_t{0xc522}) == std::uint16_t{0x44a3});

static_assert(IntMath::Reflect(std::uint32_t{0x00000000}) == std::uint32_t{0x00000000});
static_assert(IntMath::Reflect(std::uint32_t{0xffffffff}) == std::uint32_t{0xffffffff});
static_assert(IntMath::Reflect(std::uint32_t{0xa5ca418c}) == std::uint32_t{0x318253a5});
static_assert(IntMath::Reflect(std::uint32_t{0x84218421}) == std::uint32_t{0x84218421});
static_assert(IntMath::Reflect(std::uint32_t{0xd6db09a4}) == std::uint32_t{0x2590db6b});
static_assert(IntMath::Reflect(std::uint32_t{0x8f6c43c5}) == std::uint32_t{0xa3c236f1});
static_assert(IntMath::Reflect(std::uint32_t{0xea85be38}) == std::uint32_t{0x1c7da157});
static_assert(IntMath::Reflect(std::uint32_t{0xe7f72b2c}) == std::uint32_t{0x34d4efe7});

static_assert(IntMath::Reflect(std::uint64_t{0x0000000000000000}) == std::uint64_t{0x0000000000000000});
static_assert(IntMath::Reflect(std::uint64_t{0xffffffffffffffff}) == std::uint64_t{0xffffffffffffffff});
static_assert(IntMath::Reflect(std::uint64_t{0x124884213579eca8}) == std::uint64_t{0x15379eac84211248});
static_assert(IntMath::Reflect(std::uint64_t{0x7826e2e9ea000ed5}) == std::uint64_t{0xab7000579747641e});
static_assert(IntMath::Reflect(std::uint64_t{0x3507f3d820833719}) == std::uint64_t{0x98ecc1041bcfe0ac});
static_assert(IntMath::Reflect(std::uint64_t{0x0101b43f6d17de8e}) == std::uint64_t{0x717be8b6fc2d8080});
static_assert(IntMath::Reflect(std::uint64_t{0x0355ea48d3874068}) == std::uint64_t{0x1602e1cb1257aac0});
static_assert(IntMath::Reflect(std::uint64_t{0x6ba0cdcf77cff1c1}) == std::uint64_t{0x838ff3eef3b305d6});
static_assert(IntMath::Reflect(std::uint64_t{0x9dbeb90e4f225f0c}) == std::uint64_t{0x30fa44f2709d7db9});
static_assert(IntMath::Reflect(std::uint64_t{0xe51717a72902214a}) == std::uint64_t{0x52844094e5e8e8a7});
static_assert(IntMath::Reflect(std::uint64_t{0x691f71cbcddb4574}) == std::uint64_t{0x2ea2dbb3d38ef896});

constexpr auto LoopCount = 100 * (1 << 20);

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

template<std::unsigned_integral U>
bool Test(auto& rng) {
  for (int i = LoopCount; i--; ) {
    auto x = static_cast<U>(rng());
    if (tjg::Reflect(x) != IntMath::Reflect(x))
      return false;
  }
  return true;
} // Test

using Clock = std::chrono::high_resolution_clock;
struct TimedResult {
  std::chrono::milliseconds elapsed;
  std::uint64_t result;
  TimedResult(auto dt, std::uint64_t res)
    : elapsed{std::chrono::duration_cast<std::chrono::milliseconds>(dt)}
    , result{res}
    { }
}; // TimedResult

template<std::unsigned_integral U>
auto TimedTestTjg() {
  using Rng = std::conditional_t<sizeof(U)<=sizeof(std::uint32_t),
                                 std::mt19937, std::mt19937_64>;
  auto rng = Rng{12345};
  auto result = U{0};
  auto start = Clock::now();
  for (auto i = LoopCount; i--; )
    result ^= tjg::Reflect(static_cast<U>(rng()));
  auto stop = Clock::now();
  return TimedResult{stop-start, result};
} // TimedTestTjg

template<std::unsigned_integral U>
auto TimedTestInt() {
  using Rng = std::conditional_t<sizeof(U)<=sizeof(std::uint32_t),
                                 std::mt19937, std::mt19937_64>;
  auto rng = Rng{12345};
  auto result = U{0};
  auto start = Clock::now();
  for (auto i = LoopCount; i--; )
    result ^= IntMath::Reflect(static_cast<U>(rng()));
  auto stop = Clock::now();
  return TimedResult{stop-start, result};
} // TimedTestInt

template<std::unsigned_integral U>
bool TimedTest() {
  auto intResult = TimedTestInt<U>();
  auto tjgResult = TimedTestTjg<U>();
  std::cout << std::setw(8) << TypeName<U>()
            << '\t' << tjgResult.elapsed << '\t' << intResult.elapsed;
  bool result = (tjgResult.result == intResult.result);
  if (!result)
    std::cout << " WRONG!";
  std::cout << '\n';
  return result;
} // TimedTest

int main() {
  using namespace std;

  int failCount = 0;
  std::cout << "Type    \tOld\tNew\n";
  failCount += !TimedTest<std::uint8_t >();
  failCount += !TimedTest<std::uint16_t>();
  failCount += !TimedTest<std::uint32_t>();
  failCount += !TimedTest<std::uint64_t>();

  if (failCount > 0) {
    std::cout << "Failed " << failCount << "/4 tests." << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
} // main

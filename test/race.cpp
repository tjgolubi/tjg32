#include "tjg/Reflect.hpp"
#include "tjg/bit_reverse.hpp"
#include "tjg/SaveIo.hpp"

#include <chrono>
#include <vector>
#include <map>
#include <ranges>
#include <algorithm>
#include <random>
#include <concepts>
#include <iostream>
#include <iomanip>
#include <utility>
#include <type_traits>
#include <limits>
#include <cstddef>
#include <cstdlib>

using Clock = std::chrono::steady_clock;

constexpr std::size_t DataSize = (1 << 20);
constexpr int LoopCount = 1000;

template<std::unsigned_integral T>
constexpr T ReflectBits(T x) noexcept {
  constexpr auto Bits = std::numeric_limits<T>::digits;
  auto result = T{0};
  for (int i = 0; i != Bits; ++i) {
    result <<= 1;
    result |= (x & T{1});
    x >>= 1;
  }
  return result;
} // ReflectBits

struct TestResult {
  int failed = 0;
  Clock::duration dt = Clock::duration::zero();

  TestResult& operator+=(const TestResult& rhs) noexcept {
    failed += rhs.failed;
    dt     += rhs.dt;
    return *this;
  }
}; // TestResult

using ResultMap = std::map<std::string, TestResult>;
ResultMap TestResults;

using TestType = std::uint64_t;
using DataVec = std::vector<TestType>;
DataVec Data;
DataVec Expect;

using TestFn = TestType (*)(TestType) noexcept;

[[nodiscard]]
bool Test(const std::string& name, TestFn f) {
  int failed = 0;
  auto start = Clock::now();
  for (int i = 0; i != std::ssize(Data); ++i)
    failed += (f(Data[i]) != Expect[i]);
  auto stop  = Clock::now();
  TestResults[name] += TestResult{failed, stop - start};
  return (failed != 0);
} // Test

int main() {
  using tjg::uint128_t;
  constexpr auto Seed = 12345;
  std::mt19937_64 rng{Seed};

  std::cerr << "Generating random values " << std::flush;
  // Fill data with pseudo-random values
  {
    rng.seed(Seed);
    Data.reserve(DataSize);
    for (int i = 0; i != DataSize; ++i) {
      if constexpr (sizeof(TestType) <= sizeof(std::uint64_t)) {
        Data.push_back(TestType(rng()));
      }
      else {
        auto x1 = uint128_t{rng()};
        auto x2 = uint128_t{rng()};
        Data.push_back(TestType((x1 << 64) | x2));
      }
    }
  }
  std::cerr << "done." << std::endl;

  std::cerr << "Generating solutions " << std::flush;

  // std::ranges::transform(Data, std::back_inserter(Expect), ReflectBits);
  for (auto d: Data)
    Expect.push_back(ReflectBits(d));
  std::cerr << "done." << std::endl;

  int failed = 0;

  (void) Test("bit_reverse", tjg::bit_reverse);
  (void) Test("Reflect",     tjg::IntMath::Reflect);
  for (auto& [name, r]: TestResults)
    r = TestResult{};

  for (int i = 0; i != LoopCount; ++i) {
    failed += Test("bit_reverse", tjg::bit_reverse);
    failed += Test("Reflect",     tjg::IntMath::Reflect);
  }

  {
    using namespace std;
    using namespace std::chrono;
    cout << fixed << setprecision(4);
    for (const auto& [name, res]: TestResults) {
      auto s = duration<double>(res.dt);
      cout << left << setw(12) << name << right << ' ' << setw(10) << s
           << ' ' << setw(10) << res.failed << '\n';
    }
  }

  if (failed != 0) {
    std::cout << "\nFailed " << failed << " tests.\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
} // main

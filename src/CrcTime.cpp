#include "CrcEngine.h"
#include "CrcKnown.h"
#include "CrcTraits.h"
#include "SaveIo.h"

#include <chrono>
#include <vector>
#include <array>
#include <initializer_list>
#include <span>
#include <random>
#include <concepts>
#include <iostream>
#include <iomanip>
#include <utility>
#include <type_traits>
#include <cstddef>
#include <cstdlib>

using Clock = std::chrono::high_resolution_clock;

template<std::unsigned_integral U>
struct CoutType: public std::conditional<(sizeof(U) == 1), unsigned, U> { };

template<std::unsigned_integral U>
auto Value(U x) -> typename CoutType<U>::type
  { return static_cast<typename CoutType<U>::type>(x); }

struct TimedCrc {
  std::uint64_t crc        = std::uint64_t{0};
  Clock::duration elapsed  = Clock::duration{};
}; // TimedCrc

namespace detail {

template<class CrcTraits>
auto RunCrcTestVariant(std::span<const std::byte> data) {
  std::cerr << ' ' << CrcTraits::Slices << std::flush;

  auto start = Clock::now();
  tjg::CrcKnown<CrcTraits> crc;
  crc.update(data);
  auto result = crc.value();
  auto stop = Clock::now();

  return TimedCrc{result, stop - start};
} // RunCrcTestVariant

template<class CrcTraits, int Slices_>
struct WithSlices: CrcTraits {
  static constexpr int Slices = Slices_;  // hide/override base class
}; // WithSlices

} // detail

template<class CrcTraits, int... SliceVals>
auto RunSlices(std::span<const std::byte> data) {
  auto save = tjg::SaveIo{std::cerr};
  std::cerr << "Running " << std:: setw(20) << std::left
            << CrcTraits::Name << std::right << std::flush;

  std::vector<TimedCrc> results;
  results.reserve(sizeof...(SliceVals));

  (results.emplace_back(
     detail::RunCrcTestVariant<detail::WithSlices<CrcTraits, SliceVals>>(data)), ...);

  std::cerr << std::endl;
  return results;
} // RunSlices

template<class CrcTraitsList, int... SliceVals>
bool TestCrcTraits(std::span<const std::byte> data) {
  using Results =
                std::vector<std::pair<std::string_view, std::vector<TimedCrc>>>;
  Results results;
  results.reserve(meta::LengthV<CrcTraitsList>);

  auto sums = std::array<Clock::duration, sizeof...(SliceVals)>{};

  meta::ForEachType<CrcTraitsList>([&]<class CrcTraits>() {
    auto rv = RunSlices<CrcTraits, SliceVals...>(data);
    for (int i = 0; i != std::ssize(rv); ++i)
      sums[i] += rv[i].elapsed;
    results.emplace_back(CrcTraits::Name, std::move(rv));
  });

  bool testResult = true;
  {
    using namespace std;
    auto save = tjg::SaveIo{cout};
    for (const auto& [name, rv]: results) {
      const auto crc = rv.front().crc;
      cout << '\n' << left << setfill(' ') << setw(20) << name
           << right << dec << setfill(' ') << fixed << setprecision(1);
      for (const auto& result: rv) {
        auto s = std::chrono::duration<double>(result.elapsed);
        auto rate = static_cast<double>(data.size()) / (1 << 20) / s.count();
        cout << setw(8) << rate;
      }
      for (const auto& result: rv) {
        if (result.crc != crc) {
          cout << " CRC WRONG!";
          testResult = false;
          break;
        }
      }
    }
    cout << '\n' << left << setw(20) << "Average (MiB/s):" << right;
    for (auto elapsed: sums) {
      auto s = std::chrono::duration<double>(elapsed) / results.size();
      auto rate = static_cast<double>(data.size()) / (1 << 20) / s.count();
      cout << setw(8) << rate;
    }
    cout << endl;
  }
  return testResult;
} // TestCrcTraits

template<class CrcTraitsList, int... SliceVals> inline
bool TestCrcTraits(std::span<const std::byte> data,
                   std::integer_sequence<int, SliceVals...>)
{ return TestCrcTraits<CrcTraitsList, SliceVals...>(data); }

int main() {
  constexpr auto Seed = 12345;
  std::mt19937 rng{Seed};

  std::cerr << "Generating random bytes " << std::flush;
  // Fill data with pseudo-random bytes
  std::vector<std::byte> data;
  {
    rng.seed(Seed);
    constexpr std::size_t Size = 10 << 20;  // 10 MiB
    data.reserve(Size);
    for (int i = 0; i != Size; ++i)
      data.push_back(static_cast<std::byte>(rng() & 0xff));
  }
  std::cerr << "done." << std::endl;

  using CrcSets =
    meta::TypeList<tjg::KnownAbnormalCrcs,
                   tjg::Known8BitCrcs,  tjg::Known16BitCrcs,
                   tjg::Known32BitCrcs, tjg::Known64BitCrcs>;

  using Slices = std::integer_sequence<int, 0, 1, 2, 4, 8>;

  meta::ForEachType<CrcSets>([&]<class CrcTraitsList>() {
    std::cout << "\nLSB Tests\n";
    using LsbCrcs = meta::FilterT<tjg::IsLsbFirst::template apply, CrcTraitsList>;
    (void) TestCrcTraits<LsbCrcs>(data, Slices{});
    std::cout << "\nMSB Tests\n";
    using MsbCrcs = meta::FilterT<tjg::IsMsbFirst::template apply, CrcTraitsList>;
    (void) TestCrcTraits<MsbCrcs>(data, Slices{});
  });

  return EXIT_SUCCESS;
} // main

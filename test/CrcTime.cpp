#include "crc/CrcKnown.hpp"

#include "tjg/SaveIo.hpp"
#include "tjg/meta.hpp"

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

constexpr std::size_t DataSize = (1 << 20);
constexpr int LoopCount = 10;

template<std::unsigned_integral U>
struct CoutType: public std::conditional<(sizeof(U) == 1), unsigned, U> { };

template<std::unsigned_integral U>
auto Value(U x) -> typename CoutType<U>::type
  { return static_cast<typename CoutType<U>::type>(x); }

struct TimedCrc {
  std::uint64_t crc        = std::uint64_t{0};
  Clock::duration elapsed  = Clock::duration{};
}; // TimedCrc

template<class CrcTraits>
auto RunCrcTestVariantBits(std::span<const std::byte> data) {
  std::cerr << " b" << std::flush;

  using Crc = tjg::crc::Known<CrcTraits, 0>;
  auto start = Clock::now();
  Crc crc;
  for (int i = 0; i != LoopCount; ++i) {
    for (auto b: data) {
      for (int j = 0; j != 8; ++j) {
        if constexpr (CrcTraits::ReflectIn) {
          crc.update(static_cast<bool>(b & std::byte{0x01}));
          b >>= 1;
        } else {
          crc.update(static_cast<bool>(b & std::byte{0x80}));
          b <<= 1;
        }
      }
    }
  }
  auto result = crc;
  auto stop = Clock::now();

  return TimedCrc{result, stop - start};
} // RunCrcTestVariantBits

template<class CrcTraits, std::size_t SliceVal>
auto RunCrcTestVariantBytes(std::span<const std::byte> data) {
  std::cerr << " B" << std::flush;

  using Crc = tjg::crc::Known<CrcTraits, SliceVal>;
  auto start = Clock::now();
  Crc crc;
  for (int i = 0; i != LoopCount; ++i) {
    for (auto b: data)
      crc(b);
  }
  auto result = crc;
  auto stop = Clock::now();

  return TimedCrc{result, stop - start};
} // RunCrcTestVariantBytes

template<class CrcTraits, std::size_t SliceVal>
auto RunCrcTestVariant(std::span<const std::byte> data) {
  std::cerr << ' ' << SliceVal << std::flush;

  using Crc = tjg::crc::Known<CrcTraits, SliceVal>;
  auto start = Clock::now();
  Crc crc;
  for (int i = 0; i != LoopCount; ++i)
    crc(data);
  auto result = crc;
  auto stop = Clock::now();

  return TimedCrc{result, stop - start};
} // RunCrcTestVariant

template<class CrcTraits, std::size_t... SliceVals>
auto RunSlices(std::span<const std::byte> data) {
  auto save = tjg::SaveIo{std::cerr};
  std::cerr << "Running " << std:: setw(20) << std::left
            << CrcTraits::Name << std::right << std::flush;

  std::vector<TimedCrc> results;
  results.reserve(3 + sizeof...(SliceVals));
  results.emplace_back(RunCrcTestVariantBits<CrcTraits>(data));
  results.emplace_back(RunCrcTestVariantBytes<CrcTraits, 0>(data));
  results.emplace_back(RunCrcTestVariantBytes<CrcTraits, 1>(data));

  (results.emplace_back(RunCrcTestVariant<CrcTraits, SliceVals>(data)), ...);

  std::cerr << std::endl;
  return results;
} // RunSlices

template<class CrcTraitsList, std::size_t... SliceVals>
bool TestCrcTraits(std::span<const std::byte> data) {
  using Results =
                std::vector<std::pair<std::string_view, std::vector<TimedCrc>>>;
  Results results;
  results.reserve(meta::SizeV<CrcTraitsList>);

  meta::ForEachType<CrcTraitsList>([&]<class CrcTraits>() {
    auto rv = RunSlices<CrcTraits, SliceVals...>(data);
    results.emplace_back(CrcTraits::Name, std::move(rv));
  });

  bool testResult = true;
  {
    using namespace std;
    auto save = tjg::SaveIo{cout};
    for (const auto& [name, rv]: results) {
      const auto crc = rv.front().crc;
      cout << '\n' << left << setfill(' ') << setw(20) << name
           << right << dec << setfill(' ') << fixed << setprecision(0);
      for (const auto& result: rv) {
        auto s = std::chrono::duration<double>(result.elapsed);
        auto rate = static_cast<double>(data.size() * LoopCount)
                  / (1 << 20) / s.count();
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

    if (!results.empty()) {
      auto sums = std::vector<Clock::duration>{ results.front().second.size() };
      for (const auto& [name, rv]: results) {
        for (int i = 0; i != std::ssize(rv); ++i)
          sums[i] += rv[i].elapsed;
      }

      cout << '\n' << left << setw(20) << "Average (MiB/s):" << right;
      for (auto elapsed: sums) {
        auto s = std::chrono::duration<double>(elapsed) / results.size();
        auto rate = static_cast<double>(data.size() * LoopCount)
                  / (1 << 20) / s.count();
        cout << setw(8) << rate;
      }
    }
    cout << endl;
  }
  return testResult;
} // TestCrcTraits

template<class CrcTraitsList, std::size_t... SliceVals> inline
bool TestCrcTraits(std::span<const std::byte> data,
                   std::index_sequence<SliceVals...>)
{ return TestCrcTraits<CrcTraitsList, SliceVals...>(data); }

int main() {
  constexpr auto Seed = 12345;
  std::mt19937 rng{Seed};

  std::cerr << "Generating random bytes " << std::flush;
  // Fill data with pseudo-random bytes
  std::vector<std::byte> data;
  {
    rng.seed(Seed);
    data.reserve(DataSize);
    for (int i = 0; i != DataSize; ++i)
      data.push_back(static_cast<std::byte>(rng() & 0xff));
  }
  std::cerr << "done." << std::endl;

  using namespace tjg::crc::test_detail;

  using CrcSets =
    meta::TypeList<KnownAbnormalCrcs,
                   Known8BitCrcs,  Known16BitCrcs,
                   Known32BitCrcs, Known64BitCrcs>;

  using Slices = std::index_sequence<0, 1, 2, 4, 8>;

  int failed = 0;
  meta::ForEachType<CrcSets>([&]<class CrcTraitsList>() {
    std::cout << "\nLSB Tests\n";
    using LsbCrcs = meta::FilterT<IsLsbFirst::template apply, CrcTraitsList>;
    failed += !TestCrcTraits<LsbCrcs>(data, Slices{});
    std::cout << "\nMSB Tests\n";
    using MsbCrcs = meta::FilterT<IsMsbFirst::template apply, CrcTraitsList>;
    failed += !TestCrcTraits<MsbCrcs>(data, Slices{});
  });

  std::cout << "\nDefacto CRCs\n";

  {
    using namespace tjg::crc;
    using DefactoCrcs = meta::TypeList<Crc8::Traits,  Crc16::Traits,
                                       Crc32::Traits, Crc64::Traits>;
    failed += !TestCrcTraits<DefactoCrcs>(data, Slices{});
  }

  if (failed != 0) {
    std::cout << "\nFailed " << failed << " tests.\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
} // main

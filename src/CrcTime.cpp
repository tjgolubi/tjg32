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
  std::cout << ' ' << CrcTraits::Slices << std::flush;

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
  std::cout << "Running " << CrcTraits::Name << std::flush;

  std::vector<TimedCrc> results;
  results.reserve(sizeof...(SliceVals));

  (results.emplace_back(
     detail::RunCrcTestVariant<detail::WithSlices<CrcTraits, SliceVals>>(data)), ...);

  std::cout << std::endl;
  return results;
} // RunSlices

int main() {
  constexpr auto Seed = 12345;
  std::mt19937 rng{Seed};

  std::cout << "Generating random bytes" << std::flush;
  // Fill data with pseudo-random bytes
  std::vector<std::byte> data;
  {
    rng.seed(Seed);
    constexpr std::size_t Size = 10 << 20;  // 10 MiB
    data.reserve(Size);
    for (int i = 0; i != Size; ++i)
      data.push_back(static_cast<std::byte>(rng() & 0xff));
  }

  using Results =
                std::vector<std::pair<std::string_view, std::vector<TimedCrc>>>;
  Results results;
  results.reserve(meta::LengthV<tjg::KnownCrcs>);

  meta::ForEachType<tjg::KnownCrcs>([&]<class CrcTraits>() {
    results.emplace_back(
                CrcTraits::Name, RunSlices<CrcTraits, 0, 1, 2, 4, 8>(data));
  });

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
          break;
        }
      }
    }
    cout << endl;
  }

  return EXIT_SUCCESS;
} // main

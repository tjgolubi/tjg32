#include "meta.h"

#include <chrono>
#include <random>
#include <span>
#include <array>
#include <vector>
#include <functional>
#include <concepts>
#include <type_traits>
#include <utility>
#include <cstdint>
#include <cstddef>

#include <iostream>
#include <iomanip>

namespace detail {

consteval std::uint8_t Reflect8(std::uint8_t in) {
  auto i = 8 - 1;
  std::uint8_t out = (in & 1);
  do {
    in >>= 1;
    out = (out << 1) | (in & 1);
  } while (--i);
  return out;
} // Reflect8

consteval std::array<std::uint8_t, 256> GenerateReflectTable() {
  std::array<std::uint8_t, 256> table{};
  for (unsigned i = 0; i != 256; ++i)
    table[i] = Reflect8(static_cast<std::uint8_t>(i));
  return table;
}

} // detail

template<std::integral T>
requires (sizeof(T) == 1)
constexpr T Reflect(T x) noexcept {
  static constexpr std::array<std::uint8_t, 256> Table
                                              = detail::GenerateReflectTable();
  return static_cast<T>(Table[static_cast<std::uint8_t>(x)]);
}

constexpr std::byte Reflect(std::byte x) noexcept
  { return std::byte{Reflect(std::to_integer<std::uint8_t>(x))}; }

template<std::integral T>
requires (sizeof(T) > 1)
constexpr T Reflect(T in) noexcept {
  auto size = sizeof(T)-1;
  T out = Reflect(static_cast<std::uint8_t>(in & 0xff));
  do {
    in >>= 8;
    out = (out << 8) | Reflect(static_cast<std::uint8_t>(in & 0xff));
  } while (--size);
  return out;
} // Reflect

template<std::unsigned_integral Uint, Uint Poly>
struct NaiveCrc {
  static constexpr auto Name = "NaiveCrc";
  using crc_type = Uint;
  static constexpr auto Rpoly = Reflect(Poly);

  static constexpr Uint Update(Uint crc, std::byte in) {
    for (int i = 0; i != 8; ++i) {
      auto lsb = static_cast<bool>(
                        (std::byte{(std::uint8_t)crc} ^ in) & std::byte{0x01});
      crc >>= 1;
      if (lsb)
        crc ^= Rpoly;
      in >>= 1;
    }
    return crc;
  } // Update

  static constexpr Uint Update(Uint crc, std::span<const std::byte> buf) {
    for (auto b: buf)
      crc = Update(crc, b);
    return crc;
  }
}; // NaiveCrc

template<std::unsigned_integral Uint, Uint Poly>
struct PlainCrc {
  static constexpr auto Name = "PlainCrc";
  using crc_type = Uint;
  static constexpr auto Rpoly = Reflect(Poly);

  static constexpr Uint Update(Uint crc, std::byte in) {
    crc ^= std::to_integer<Uint>(in);
    for (int i = 0; i != 8; ++i) {
      auto lsb = static_cast<bool>(crc & Uint{1});
      crc >>= 1;
      if (lsb)
        crc ^= Rpoly;
    }
    return crc;
  } // Update

  static constexpr Uint Update(Uint crc, std::span<const std::byte> buf) {
    for (auto b: buf)
      crc = Update(crc, b);
    return crc;
  }
}; // PlainCrc

// CRC_MASK_WORD evaluates to either 0 or ~0, depending on the MSB of its
// argument.  The first DEBUG implementation runs faster when compiled
// with -O0 or -Og.  For all other optimization levels, the second wins.
#ifndef DEBUG
#define CRC_MASK_WORD(x) (-(Uint)((Int)(x) < Int{0}))
#else
#define CRC_MASK_WORD(x) ((Uint)((Int)(x) >> Shift))
#endif

template<std::unsigned_integral Uint, Uint Poly>
struct TradLsbCrc {
  static constexpr auto Name = "TradLsbCrc";
  using crc_type = Uint;

private:
  static constexpr auto Rpoly = Reflect(Poly);
  using Int = std::make_signed_t<Uint>;
  [[maybe_unused]] static constexpr auto Shift = 8 * sizeof(Uint) - 1;

public:
  // Optimized to remove if-statement.
  static constexpr Uint Update(Uint crc, std::byte in) {
    crc ^= std::to_integer<Uint>(in);
    for (int i = 0; i != 8; ++i)
      crc = (crc >> 1) ^ (CRC_MASK_WORD(crc << Shift) & Rpoly);
    return crc;
  }

  static constexpr Uint Update(Uint crc, std::span<const std::byte> buf) {
    for (auto b: buf)
      crc = Update(crc, b);
    return crc;
  }
}; // TradLsbCrc

template<std::unsigned_integral Uint, Uint Poly>
struct TradMsbCrc {
  static constexpr auto Name = "TradMsbCrc";
  using crc_type = Uint;

private:
  using Int = std::make_signed_t<Uint>;
  [[maybe_unused]] static constexpr auto Shift = 8 * sizeof(Uint) - 1;

public:
  // Optimized to remove if-statement.
  static constexpr Uint Update(Uint crc, std::byte in) {
    crc ^= std::to_integer<Uint>(in) << (8 * (sizeof(Uint) - 1));
    for (int i = 0; i != 8; ++i)
      crc = (crc << 1) ^ (CRC_MASK_WORD(crc) & Poly);
    return crc;
  }

  static constexpr Uint Update(Uint crc, std::span<const std::byte> buf) {
    for (auto b: buf)
      crc = Update(crc, b);
    return crc;
  }
}; // TradMsbCrc


template<std::unsigned_integral Uint, Uint Poly>
class GenLsbCrc {
public:
  static constexpr auto Name = "GenLsbCrc";
  using crc_type = Uint;

private:
  static constexpr auto Rpoly = Reflect(Poly);

  template<std::size_t N>
  static constexpr Uint Residual() {
    if constexpr (N > 1)
      return Uint{0};
    else
      return Rpoly >> (1 - N);
  }

  template<std::size_t N>
  static constexpr Uint Iter(Uint crc) {
    using Int = std::make_signed_t<Uint>;
    constexpr auto Shift = 8 * sizeof(Uint) - 1;
    return static_cast<Uint>( (((Int)crc << (Shift - N)) >> Shift)
                              & ((Rpoly >> (7 - N)) ^ Residual<N>()));
  }

  template<std::size_t... N>
  static constexpr Uint IterateCrc(Uint crc, std::index_sequence<N...>)
    { return (Iter<N>(crc) ^ ...); }

public:
  static constexpr Uint Update(Uint crc, std::byte in) {
    crc ^= std::to_integer<Uint>(in);
    crc = (crc >> 8) ^ IterateCrc(crc, std::make_index_sequence<8>{});
    return crc;
  }

  static constexpr Uint Update(Uint crc, std::span<const std::byte> buf) {
    for (auto b: buf)
      crc = Update(crc, b);
    return crc;
  }
}; // GenLsbCrc

template<std::unsigned_integral Uint, Uint Poly>
class GenMsbCrc {
public:
  static constexpr auto Name = "GenMsbCrc";
  using crc_type = Uint;

private:
  template<std::size_t N>
  static constexpr Uint Residual() {
    if constexpr (N > 1)
      return Uint{0};
    else
      return Poly << (1 - N);
  }

  template<std::size_t N>
  static constexpr Uint Iter(Uint crc) {
    using Int = std::make_signed_t<Uint>;
    constexpr auto Shift = 8 * sizeof(Uint) - 1;
    return static_cast<Uint>( (((Int)crc << N) >> Shift)
                              & ((Poly << (7 - N)) ^ Residual<N>()));
  }

  template<std::size_t... N>
  static constexpr Uint IterateCrc(Uint crc, std::index_sequence<N...>)
    { return (Iter<N>(crc) ^ ...); }

public:
  static constexpr Uint Update(Uint crc, std::byte in) {
    crc ^= std::to_integer<Uint>(in) << (8 * (sizeof(Uint) - 1));
    crc = (crc << 8) ^ IterateCrc(crc, std::make_index_sequence<8>{});
    return crc;
  }

  static constexpr Uint Update(Uint crc, std::span<const std::byte> buf) {
    for (auto b: buf)
      crc = Update(crc, b);
    return crc;
  }
}; // GenMsbCrc

template<std::unsigned_integral Uint, Uint Poly>
class MsbCrc {
public:
  static constexpr auto Name = "MsbCrc";
  using crc_type = Uint;

  static constexpr Uint Update(Uint crc, std::byte in) {
    using Int = std::make_signed_t<Uint>;
    [[maybe_unused]] constexpr auto Shift = 8 * sizeof(Uint) - 1;
    crc ^= std::to_integer<Uint>(in) << (8 * (sizeof(Uint) - 1));
    auto c = (CRC_MASK_WORD(crc << 0) & ((Poly << 7) ^ (Poly << 1)))
           ^ (CRC_MASK_WORD(crc << 1) & ((Poly << 6) ^ (Poly << 0)))
           ^ (CRC_MASK_WORD(crc << 2) &  (Poly << 5))
           ^ (CRC_MASK_WORD(crc << 3) &  (Poly << 4))
           ^ (CRC_MASK_WORD(crc << 4) &  (Poly << 3))
           ^ (CRC_MASK_WORD(crc << 5) &  (Poly << 2))
           ^ (CRC_MASK_WORD(crc << 6) &  (Poly << 1))
           ^ (CRC_MASK_WORD(crc << 7) &  (Poly << 0));
    return (crc << 8) ^ static_cast<Uint>(c);
  }

  static constexpr Uint Update(Uint crc, std::span<const std::byte> buf) {
    for (auto b: buf)
      crc = Update(crc, b);
    return crc;
  }
}; // MsbCrc

template<std::unsigned_integral Uint, Uint Poly>
class LsbCrc {
public:
  static constexpr auto Name = "LsbCrc";
  using crc_type = Uint;

private:
  static constexpr auto Rpoly = Reflect(Poly);

public:
  static constexpr Uint Update(Uint crc, std::byte in) {
    using Int = std::make_signed_t<Uint>;
    constexpr auto Shift = 8 * sizeof(Uint) - 1;
    crc ^= std::to_integer<Uint>(in);
    auto c = (CRC_MASK_WORD(crc << (Shift-0)) & ((Rpoly >> 7) ^ (Rpoly >> 1)))
           ^ (CRC_MASK_WORD(crc << (Shift-1)) & ((Rpoly >> 6) ^ (Rpoly >> 0)))
           ^ (CRC_MASK_WORD(crc << (Shift-2)) &  (Rpoly >> 5))
           ^ (CRC_MASK_WORD(crc << (Shift-3)) &  (Rpoly >> 4))
           ^ (CRC_MASK_WORD(crc << (Shift-4)) &  (Rpoly >> 3))
           ^ (CRC_MASK_WORD(crc << (Shift-5)) &  (Rpoly >> 2))
           ^ (CRC_MASK_WORD(crc << (Shift-6)) &  (Rpoly >> 1))
           ^ (CRC_MASK_WORD(crc << (Shift-7)) &  (Rpoly >> 0));
    return (crc >> 8) ^ static_cast<Uint>(c);
  }

  static constexpr Uint Update(Uint crc, std::span<const std::byte> buf) {
    for (auto b: buf)
      crc = Update(crc, b);
    return crc;
  }
}; // LsbCrc

#undef CRC_MASK_WORD

struct TimeResult {
  std::uint32_t crc = std::uint32_t{0};
  std::chrono::milliseconds ms  = std::chrono::milliseconds{0};
}; // TimeResult

constexpr TimeResult Time(std::regular_invocable auto f) {
  using namespace std::chrono;
  auto start = steady_clock::now();
  auto crc = f();
  auto end = steady_clock::now();
  return TimeResult{crc, duration_cast<milliseconds>(end - start)};
}

template<class Crc>
TimeResult Test(int count, std::span<const std::byte> data) {
  using Uint = Crc::crc_type;
  std::cout << "Running " << Crc::Name<< std::flush;
  auto result = Time([&]() {
    auto crc = ~Uint{0};
    for (int i=0; i != count; ++i)
      crc = Crc::Update(crc, data);
    return ~crc;
  });
  std::cout << std::endl;
  return result;
} // Test

struct SaveIo {
  std::ostream& os;
  char fill;
  std::ios_base::fmtflags flags;
  explicit SaveIo(std::ostream& os_ = std::cout)
    : os{os_}, fill{os_.fill()}, flags{os_.flags()} { }
  ~SaveIo() {
    (void) os.fill(fill);
    (void) os.flags(flags);
  }
}; // SaveIo

std::ostream& SetHex(std::ostream& os = std::cout) noexcept {
  return os << std::hex << std::setfill('0') << std::internal << std::showbase;
}

int main() {
  using Uint = std::uint32_t;
  static constexpr auto NormalPoly  = Uint{0X04c11db7};
  static constexpr auto ReflectPoly = Reflect(NormalPoly);

  {
    using namespace std;
    auto save = SaveIo{cout};
    SetHex(cout);
    cout << "Using NormalPoly="  << setw(10) << NormalPoly
              << " ReflectPoly=" << setw(10) << ReflectPoly
              << endl;
  }

  using Naive    = NaiveCrc      <Uint, NormalPoly>;
  using Plain    = PlainCrc      <Uint, NormalPoly>;
  using TradLsb  = TradLsbCrc    <Uint, NormalPoly>;
  using TradMsb  = TradMsbCrc    <Uint, NormalPoly>;
  using GenLsb   = GenLsbCrc     <Uint, NormalPoly>;
  using GenMsb   = GenMsbCrc     <Uint, NormalPoly>;
  using Lsb      = LsbCrc        <Uint, NormalPoly>;
  using Msb      = MsbCrc        <Uint, NormalPoly>;

  using Crcs  = meta::TypeList<TradLsb, Lsb, GenLsb>;
  using RCrcs = meta::TypeList<GenMsb, Msb, TradMsb>;

  {
    using namespace std;
    auto buf = array{ '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    using Crc =TradLsbCrc<Uint, NormalPoly>;
    auto crc = ~Uint{0};
    crc = Crc::Update(crc, as_bytes(span{buf}));
    crc = ~crc;
    auto save = SaveIo{};
    SetHex();
    cout << "Test Sequence CRC = " << crc;
    cout << ((crc == 0xcbf43926) ? " correct" : " WRONG");
    cout << endl;
  }

  constexpr auto Seed = 12345;
  std::mt19937 rng{Seed};

  // Fill data with pseudo-random bytes
  std::vector<std::byte> data;
  constexpr int LoopCount = 100;
  {
    rng.seed(Seed);
    constexpr std::size_t Size = 1 << 20;  // 1 MiB
    data.reserve(Size);
    for (int i = 0; i != Size; ++i)
      data.push_back(static_cast<std::byte>(rng() & 0xff));
  }

  std::cout << "Computing expected value: " << std::flush;

  auto expected = Test<TradLsb>(LoopCount, data).crc;

  {
    auto save = SaveIo{};
    SetHex();
    std::cout << "Expected CRC is " << std::setw(10) << expected << std::endl;
  }

  std::vector<std::pair<std::string_view, TimeResult>> results;

  meta::ForEachType<Crcs>([&]<typename Crc>() {
    auto result = Test<Crc>(LoopCount, data);
    results.emplace_back(Crc::Name, result);
  });

  // Get ready to do MSB-First Crc's
  for (auto& b: data)
    b = Reflect(b);

  meta::ForEachType<RCrcs>([&]<typename Crc>() {
    auto result = Test<Crc>(LoopCount, data);
    result.crc = Reflect(result.crc); // For MSB-first only.
    results.emplace_back(Crc::Name, result);
  });

  {
    using namespace std;
    auto save = SaveIo{cout};
    SetHex(cout);
    for (int i = 0; i != std::ssize(results); ++i) {
      const auto& item = results[i];
      const auto& result = item.second;
      const auto crc = result.crc;
      cout << "\nCrc" << dec << i << "::Update = " << hex << setw(10) << crc
                                           << ' ' << setw(10) << Reflect(crc)
                                           << ' ' << item.first;
      if (crc != expected)
        std::cout << "................ \bWRONG!";
    }
    cout << endl;
  }

  {
    using namespace std;
    cout << setprecision(0) << fixed;
    for (int i = 0; i != std::ssize(results); ++i) {
      const auto& item = results[i];
      const auto& name = item.first;
      const auto& result = item.second;
      auto s = std::chrono::duration<double>(result.ms);
      auto rate = LoopCount * data.size() / s.count() / (1024*1024);
      cout << "\nCrc" << i << "::Update time: " << setw(6) << result.ms.count()
           << " ms " << setw(4) << rate << " MiB/s " << name;
    }
    cout << endl;
  }

  return EXIT_SUCCESS;
} // main

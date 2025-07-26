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

template<std::unsigned_integral Uint, Uint Poly>
struct TraditionalCrc {
  static constexpr auto Name = "TraditionalCrc";
  using crc_type = Uint;
  static constexpr auto Rpoly = Reflect(Poly);

  // Optimized to remove if-statement.
  static constexpr Uint Update(Uint crc, std::byte in) {
    crc ^= std::to_integer<Uint>(in);
    for (int i = 0; i != 8; ++i)
      crc = (crc >> 1) ^ (-(crc & Uint{1}) & Rpoly);
    return crc;
  }

  static constexpr Uint Update(Uint crc, std::span<const std::byte> buf) {
    for (auto b: buf)
      crc = Update(crc, b);
    return crc;
  }
}; // TraditionalCrc

template<std::unsigned_integral Uint, Uint Poly>
class GenericCrc1 {
public:
  static constexpr auto Name = "GenericCrc1";
  using crc_type = Uint;
  static constexpr auto Rpoly = Reflect(Poly);

private:
  static constexpr auto Shift = 8 * sizeof(Uint) - 1;

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
    return static_cast<Uint>( ((static_cast<Int>(crc) << (Shift - N)) >> Shift)
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
}; // GenericCrc1

template<std::unsigned_integral Uint, Uint Poly>
class GenericCrc2 {
public:
  static constexpr auto Name = "GenericCrc2";
  using crc_type = Uint;
  static constexpr auto Rpoly = Reflect(Poly);

private:
  template<std::size_t N>
  static constexpr Uint Residual() {
    if constexpr (N > 1)
      return Uint{0};
    else
      return Rpoly >> (1 - N);
  }

  template<std::size_t N>
  static constexpr Uint Iter(Uint crc) {
    constexpr auto Mask = Uint{1};
    return static_cast<Uint>( (-((crc >> N) & Mask))
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
}; // GenericCrc2

template<std::unsigned_integral Uint, Uint Poly>
class MsbCrc {
public:
  static constexpr auto Name = "MsbCrc";
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
    return static_cast<Uint>( (-(static_cast<Int>(crc << N) < 0))
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
}; // MsbCrc

template<std::unsigned_integral Uint, Uint Poly>
class HandMsbCrc {
public:
  static constexpr auto Name = "HandMsbCrc";
  using crc_type = Uint;

  static constexpr Uint Update(Uint crc, std::byte in) {
    using Int = std::make_signed_t<Uint>;
    crc ^= std::to_integer<Uint>(in) << (8 * (sizeof(Uint) - 1));
    auto c = (-(static_cast<Int>(crc << 0) < 0) & ((Poly << 7) ^ (Poly << 1)))
           ^ (-(static_cast<Int>(crc << 1) < 0) & ((Poly << 6) ^ (Poly << 0)))
           ^ (-(static_cast<Int>(crc << 2) < 0) &  (Poly << 5))
           ^ (-(static_cast<Int>(crc << 3) < 0) &  (Poly << 4))
           ^ (-(static_cast<Int>(crc << 4) < 0) &  (Poly << 3))
           ^ (-(static_cast<Int>(crc << 5) < 0) &  (Poly << 2))
           ^ (-(static_cast<Int>(crc << 6) < 0) &  (Poly << 1))
           ^ (-(static_cast<Int>(crc << 7) < 0) &  (Poly << 0));
    return (crc << 8) ^ static_cast<Uint>(c);
  }

  static constexpr Uint Update(Uint crc, std::span<const std::byte> buf) {
    for (auto b: buf)
      crc = Update(crc, b);
    return crc;
  }
}; // HandMsbCrc

template<std::unsigned_integral Uint, Uint Poly>
class HandCrc {
public:
  static constexpr auto Name = "HandCrc";
  using crc_type = Uint;
  static constexpr auto Rpoly = Reflect(Poly);

  static constexpr Uint Update(Uint crc, std::byte in) {
    using Int = std::make_signed_t<Uint>;
    crc ^= std::to_integer<Uint>(in);
    auto icrc = static_cast<Int>(crc);
    auto c = (((icrc << 31) >> 31) & ((Rpoly >> 7) ^ (Rpoly >> 1)))
           ^ (((icrc << 30) >> 31) & ((Rpoly >> 6) ^ (Rpoly >> 0)))
           ^ (((icrc << 29) >> 31) &  (Rpoly >> 5))
           ^ (((icrc << 28) >> 31) &  (Rpoly >> 4))
           ^ (((icrc << 27) >> 31) &  (Rpoly >> 3))
           ^ (((icrc << 26) >> 31) &  (Rpoly >> 2))
           ^ (((icrc << 25) >> 31) &  (Rpoly >> 1))
           ^ (((icrc << 24) >> 31) &  (Rpoly >> 0));
    return (crc >> 8) ^ static_cast<Uint>(c);
  }

  static constexpr Uint Update(Uint crc, std::span<const std::byte> buf) {
    for (auto b: buf)
      crc = Update(crc, b);
    return crc;
  }
}; // HandCrc

template<std::unsigned_integral Uint, Uint Poly>
class MaskCrc {
public:
  static constexpr auto Name = "MaskCrc";
  using crc_type = Uint;
  static constexpr auto Rpoly = Reflect(Poly);

  static constexpr Uint Update(Uint crc, std::byte in) {
    constexpr auto Mask = Uint{1};
    crc ^= std::to_integer<Uint>(in);
    auto c = (-((crc >> 0) & Mask) & ((Rpoly >> 7) ^ (Rpoly >> 1)))
           ^ (-((crc >> 1) & Mask) & ((Rpoly >> 6) ^ (Rpoly >> 0)))
           ^ (-((crc >> 2) & Mask) &  (Rpoly >> 5))
           ^ (-((crc >> 3) & Mask) &  (Rpoly >> 4))
           ^ (-((crc >> 4) & Mask) &  (Rpoly >> 3))
           ^ (-((crc >> 5) & Mask) &  (Rpoly >> 2))
           ^ (-((crc >> 6) & Mask) &  (Rpoly >> 1))
           ^ (-((crc >> 7) & Mask) &  (Rpoly >> 0));
    return (crc >> 8) ^ static_cast<Uint>(c);
  }

  static constexpr Uint Update(Uint crc, std::span<const std::byte> buf) {
    for (auto b: buf)
      crc = Update(crc, b);
    return crc;
  }
}; // MaskCrc

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
  static constexpr auto NormalPoly    = Uint{0x04C11DB7};
  static constexpr auto ReflectPoly = Reflect(NormalPoly);

  {
    auto save = SaveIo{std::cout};
    SetHex(std::cout);
    std::cout << "Using NormalPoly=" << std::setw(10) << NormalPoly
              << " ReflectPoly="     << std::setw(10) << ReflectPoly
              << std::endl;
  }

  using Naive = NaiveCrc      <Uint, NormalPoly>;
  using Plain = PlainCrc      <Uint, NormalPoly>;
  using Trad  = TraditionalCrc<Uint, NormalPoly>;
  using Mask  = MaskCrc       <Uint, NormalPoly>;
  using Hand  = HandCrc       <Uint, NormalPoly>;
  using Gen1  = GenericCrc1   <Uint, NormalPoly>;
  using Gen2  = GenericCrc2   <Uint, NormalPoly>;
  using Msb   = MsbCrc        <Uint, NormalPoly>;
  using HandMsb = HandMsbCrc  <Uint, NormalPoly>;

  using Crcs  = meta::TypeList<Naive, Plain, Trad, Mask, Hand, Gen1, Gen2>;
  using RCrcs = meta::TypeList<Msb, HandMsb>;

  {
    using namespace std;
    auto buf = array{ '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    using Crc =TraditionalCrc<Uint, NormalPoly>;
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

  auto expected = Test<Trad>(LoopCount, data).crc;

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

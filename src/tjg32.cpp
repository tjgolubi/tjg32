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
  auto out = std::uint8_t{0};
  for (int i=0; i!=8; ++i) {
    out = (out << 1) | (in & 1);
    in >>= 1;
  }
  return out;
}

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

template<std::integral T>
requires (sizeof(T) > 1)
constexpr T Reflect(T in) noexcept {
  auto out = T{0};
  for (int i = 0; i != sizeof(T); ++i) {
    out = (out << 8) | Reflect(static_cast<std::uint8_t>(in & 0xff));
    in >>= 8;
  }
  return out;
} // Reflect


template<std::unsigned_integral Uint, Uint Poly>
class GenericCrc {
public:
  static constexpr auto Name = "GenericCrc";

private:
  static constexpr auto Shift = 8 * sizeof(Uint) - 1;

  template<std::size_t N>
  static constexpr Uint Residual() {
    if constexpr (N > 1)
      return Uint{0};
    else
      return Poly >> (1 - N);
  }

  template<std::size_t N>
  static constexpr Uint Iter(Uint crc) {
    using Int = std::make_signed_t<Uint>;
    return static_cast<Uint>( ((static_cast<Int>(crc) << (Shift - N)) >> Shift)
                              & ((Poly >> (7 - N)) ^ Residual<N>()));
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

  static constexpr Uint Update(Uint crc, std::span<std::byte> buf) {
    for (auto b: buf)
      crc = Update(crc, b);
    return crc;
  }
}; // GenericCrc

template<std::unsigned_integral Uint, Uint Poly>
struct TraditionalCrc {
  static constexpr auto Name = "TraditionalCrc";

  // Optimized to remove if-statement.
  static constexpr Uint Update(Uint crc, std::byte in) {
    crc ^= std::to_integer<Uint>(in);
    for (int i = 0; i != 8; ++i)
      crc = (crc >> 1) ^ (-(crc & Uint{1}) & Poly);
    return crc;
  }

  static constexpr Uint Update(Uint crc, std::span<std::byte> buf) {
    for (auto b: buf)
      crc = Update(crc, b);
    return crc;
  }
}; // TraditionalCrc

template<std::unsigned_integral Uint, Uint Poly>
struct PlainCrc {
  static constexpr auto Name = "PlainCrc";

  static constexpr Uint Update(Uint crc, std::byte in) {
    crc ^= std::to_integer<Uint>(in);
    for (int i = 0; i != 8; ++i) {
      auto lsb = static_cast<bool>(crc & Uint{1});
      crc >>= 1;
      if (lsb)
        crc ^= Poly;
    }
    return crc;
  } // Update

  static constexpr Uint Update(Uint crc, std::span<std::byte> buf) {
    for (auto b: buf)
      crc = Update(crc, b);
    return crc;
  }
}; // PlainCrc

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

  using Crc0 = PlainCrc<Uint, ReflectPoly>;
  using Crc1 = TraditionalCrc<Uint, ReflectPoly>;
  using Crc2 = GenericCrc<Uint, ReflectPoly>;

  constexpr int LoopCount = 100;

  constexpr std::size_t size = 1 << 20;  // 1 MiB
  std::vector<std::byte> data;
  data.reserve(size);

  // Fill data with pseudo-random bytes
  std::mt19937 rng(12345);
  for (int i = 0; i != size; ++i)
    data.push_back(static_cast<std::byte>(rng() & 0xff));

  std::cout << "Running Crc0 " << Crc0::Name<< std::endl;
  auto result0 = Time([&]() {
    auto crc = ~Uint{0};
    for (int i=0; i != LoopCount; ++i)
      crc = Crc0::Update(crc, data);
    return ~crc;
  });

  std::cout << "Running Crc1 " << Crc1::Name << std::endl;
  auto result1 = Time([&]() {
    auto crc = ~Uint{0};
    for (int i=0; i != LoopCount; ++i)
      crc = Crc1::Update(crc, data);
    return ~crc;
  });

  std::cout << "Running Crc2 " << Crc2::Name << std::endl;
  auto result2 = Time([&]() {
    auto crc = ~Uint{0};
    for (int i=0; i != LoopCount; ++i)
      crc = Crc2::Update(crc, data);
    return ~crc;
  });

  {
    using namespace std;
    auto save = SaveIo{cout};
    SetHex(cout);
    cout << "\nCrc0::Update = " << setw(10) << result0.crc
         << "\nCrc1::Update = " << setw(10) << result1.crc
         << "\nCrc2::Update = " << setw(10) << result2.crc
         << endl;
  }

  {
    using namespace std;
    cout
      << "\nCrc0::Update time: " << setw(6) << result0.ms << ' ' << Crc0::Name
      << "\nCrc1::Update time: " << setw(6) << result1.ms << ' ' << Crc1::Name
      << "\nCrc2::Update time: " << setw(6) << result2.ms << ' ' << Crc2::Name
      << endl;
  }

  return EXIT_SUCCESS;
} // main

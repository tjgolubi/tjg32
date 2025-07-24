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

template<std::unsigned_integral Uint, Uint Poly>
class GenericCrc {
public:
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
};

template<std::unsigned_integral Uint, Uint Poly>
struct TraditionalCrc {

  // Optimized to remove if-statement.
  static constexpr Uint Update(Uint crc, std::byte in) {
    crc ^= std::to_integer<Uint>(in);
    for (int i = 0; i < 8; ++i)
      crc = (crc >> 1) ^ (-(crc & Uint{1}) & Poly);
    return crc;
  }

  static constexpr Uint Update(Uint crc, std::span<const std::byte> buf) {
    for (auto b: buf)
      crc = Update(crc, b);
    return crc;
  }

};

template<std::unsigned_integral Uint, Uint Poly>
struct PlainCrc {

  static constexpr Uint Update(Uint crc, std::byte in) {
    crc ^= std::to_integer<Uint>(in);
    for (int i = 0; i < 8; ++i) {
      bool lsb = !!(crc & Uint{1});
      crc >>= 1;
      if (lsb)
        crc ^= Poly;
    }
    return crc;
  } // Update

  static constexpr Uint Update(Uint crc, std::span<const std::byte> buf) {
    for (auto b: buf)
      crc = Update(crc, b);
    return crc;
  }

};

struct Result {
  std::uint32_t crc = std::uint32_t{0};
  std::chrono::milliseconds ms  = std::chrono::milliseconds{0};
}; // Result

constexpr Result Time(std::regular_invocable auto f) {
  using namespace std::chrono;
  auto start = steady_clock::now();
  auto crc = f();
  auto end = steady_clock::now();
  return Result{crc, duration_cast<milliseconds>(end - start)};
}

int main() {
  using Uint = std::uint32_t;
  static constexpr auto Poly = Uint{0xedb88320};
  using Crc0 = PlainCrc<Uint, Poly>;
  using Crc1 = TraditionalCrc<Uint, Poly>;
  using Crc2 = GenericCrc<Uint, Poly>;

  constexpr int LoopCount = 100;

  constexpr std::size_t size = 1 << 20;  // 1 MiB
  std::vector<std::byte> data;
  data.reserve(size);

  // Fill data with pseudo-random bytes
  std::mt19937 rng(12345);
  std::uniform_int_distribution<int> dist(0, 255);
  for (std::size_t i = 0; i < size; ++i)
    data.push_back(static_cast<std::byte>(dist(rng)));

  std::cout << "Running Crc0" << std::endl;
  auto result0 = Time([&]() {
    auto crc = ~Uint{0};
    for (int i=0; i<LoopCount; ++i)
      crc = Crc0::Update(crc, data);
    return ~crc;
  });

  std::cout << "Running Crc1" << std::endl;
  auto result1 = Time([&]() {
    auto crc = ~Uint{0};
    for (int i=0; i<LoopCount; ++i)
      crc = Crc1::Update(crc, data);
    return ~crc;
  });

  std::cout << "Running Crc2" << std::endl;
  auto result2 = Time([&]() {
    auto crc = ~Uint{0};
    for (int i=0; i<LoopCount; ++i)
      crc = Crc2::Update(crc, data);
    return ~crc;
  });

  std::cout << std::hex << std::setfill('0');
  std::cout << "Crc0::Update = " << std::setw(8) << result0.crc << '\n';
  std::cout << "Crc1::Update = " << std::setw(8) << result1.crc << '\n';
  std::cout << "Crc2::Update = " << std::setw(8) << result2.crc << '\n';

  std::cout << std::dec;
  std::cout << "Crc0::Update time: " << result0.ms << '\n';
  std::cout << "Crc1::Update time: " << result1.ms << '\n';
  std::cout << "Crc2::Update time: " << result2.ms << '\n';

  return EXIT_SUCCESS;
} // main

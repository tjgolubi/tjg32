#pragma once

#include <array>
#include <concepts>
#include <cstdint>
#include <cstddef>

namespace tjg {

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

} // tjg

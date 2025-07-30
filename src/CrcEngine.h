#include "Integer.h"

#include <span>
#include <concepts>
#include <type_traits>
#include <utility>
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

enum class CrcDir { LsbFirst, MsbFirst };

namespace detail {

#if 0
// CRC_MASK_WORD evaluates to either 0 or ~0, depending on the MSB of its
// argument.  The first DEBUG implementation runs faster when compiled
// with -O0 or -Og.  For all other optimization levels, the second wins.
#ifndef DEBUG
#define CRC_MASK_WORD(x) (-(Uint)((Int)(x) < Int{0}))
#else
#define CRC_MASK_WORD(x) ((Uint)((Int)(x) >> Shift))
#endif

template<std::unsigned_integral Uint, Uint Poly, CrcDir Dir>
requires (Dir == CrcDir::MsbFirst)
constexpr Uint Update(Uint crc, std::byte in) {
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
} // Update MsbFirst

template<std::unsigned_integral Uint, Uint Poly, CrcDir Dir>
requires (Dir == CrcDir::LsbFirst)
constexpr Uint Update(Uint crc, std::byte in) {
  using Int = std::make_signed_t<Uint>;
  constexpr auto Shift = 8 * sizeof(Uint) - 1;
  constexpr auto Rpoly = Reflect(Poly);
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
} // Update LsbFirst
#endif

template<std::unsigned_integral Uint, Uint Poly, CrcDir Dir>
requires (Dir == CrcDir::LsbFirst)
constexpr Uint TradUpdate(Uint crc, std::byte in) {
  static constexpr auto Rpoly = Reflect(Poly);
  crc ^= std::to_integer<Uint>(in);
  for (int i = 0; i != 8; ++i)
    crc = (crc >> 1) ^ (-(crc & Uint{1}) & Rpoly);
  return crc;
} // TradUpdate LsbFirst

template<std::unsigned_integral Uint, Uint Poly, CrcDir Dir>
requires (Dir == CrcDir::MsbFirst)
constexpr Uint TradUpdate(Uint crc, std::byte in) {
  using Int = std::make_signed_t<Uint>;
  crc ^= std::to_integer<Uint>(in) << 8 * (sizeof(Uint)-1);
  for (int i = 0; i != 8; ++i)
    crc = (crc >> 1) ^ (-(Uint)((Int) crc < 0) & Poly);
  return crc;
} // TradUpdate MsbFirst

} // detail

template<int Bits, uint_t<Bits>::least Poly, CrcDir Dir>
class CrcEngine {
public:
  using CrcType = uint_t<Bits>::least;
  static constexpr int     bits = Bits;
  static constexpr CrcType poly = Poly;
  static constexpr CrcDir  dir  = Dir;

private:
  const CrcType _init;
  const CrcType _xor;
  CrcType _crc;

public:
  constexpr void reset() noexcept { _crc = _init; }

  constexpr CrcType value() const noexcept {
    return _crc ^ _xor;
#if 0
    if constexpr (Dir == CrcDir::LsbFirst) {
      return Reflect(_crc) ^ _xor;
    } else {
      return _crc ^ _xor;
    }
#endif
  }

  constexpr CrcEngine(CrcType init_, CrcType xor_) noexcept
    : _init{init_}, _xor{xor_}, _crc{init_} { }

  constexpr void update(std::byte b) noexcept
    { _crc = detail::TradUpdate<CrcType, Poly, Dir>(_crc, b); }

  constexpr void update(std::span<const std::byte> buf) noexcept {
    for (auto b: buf)
      update(b);
  }
}; // CrcEngine

} // tjg
// =========================================================================

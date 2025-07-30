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
  crc ^= std::to_integer<Uint>(in) << 8 * (sizeof(Uint)-1);
  for (int i = 0; i != 8; ++i)
    crc = (crc << 1) ^ (CRC_MASK_WORD(crc) & Poly);
  return crc;
} // Update MsbFirst

template<std::unsigned_integral Uint, Uint Poly, CrcDir Dir>
requires (Dir == CrcDir::LsbFirst)
constexpr Uint Update(Uint crc, std::byte in) {
  using Int = std::make_signed_t<Uint>;
  static constexpr auto Rpoly = Reflect(Poly);
  [[maybe_unused]] constexpr auto Shift = 8 * sizeof(Uint) - 1;
  crc ^= std::to_integer<Uint>(in);
  for (int i = 0; i != 8; ++i)
    crc = (crc >> 1) ^ (CRC_MASK_WORD(crc<<Shift) & Rpoly);
  return crc;
} // Update LsbFirst

} // detail

template<std::size_t Bits, uint_t<Bits>::least Poly, CrcDir Dir>
class CrcEngine {
public:
  using CrcType = uint_t<Bits>::least;
  static constexpr auto     bits = Bits;
  static constexpr CrcType poly = Poly;
  static constexpr CrcDir  dir  = Dir;

protected:
  static constexpr std::uint8_t Shift = 8 * sizeof(CrcType) - Bits;

private:
  const CrcType _init;
  const CrcType _xor;
  CrcType _crc;

  static constexpr CrcType Init(CrcType init) noexcept {
    if constexpr (Dir == CrcDir::MsbFirst)
      return static_cast<CrcType>(init << Shift);
    else
      return static_cast<CrcType>(Reflect(init) >> Shift);
  } // Init

public:
  constexpr void reset() noexcept { _crc = _init; }

  constexpr CrcType value() const noexcept {
    if constexpr (Dir == CrcDir::MsbFirst)
      return (_crc >> Shift) ^ _xor;
    else
      return _crc ^ _xor;
  }

  constexpr CrcEngine(CrcType init_, CrcType xor_) noexcept
    : _init{Init(init_)} , _xor{xor_} , _crc{_init} { }

  constexpr void update(std::byte b) noexcept
    { _crc = detail::Update<CrcType, Poly<<Shift, Dir>(_crc, b); }

  constexpr void update(std::span<const std::byte> buf) noexcept {
    for (auto b: buf)
      update(b);
  }
}; // CrcEngine

} // tjg

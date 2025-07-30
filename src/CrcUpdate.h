#pragma once

#include "Reflect.h"

#include <concepts>
#include <type_traits>
#include <cstddef>

namespace tjg {

enum class CrcDir { LsbFirst, MsbFirst };

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
constexpr Uint CrcUpdate(Uint crc, std::byte in) {
  using Int = std::make_signed_t<Uint>;
  [[maybe_unused]] constexpr auto Shift = 8 * sizeof(Uint) - 1;
  crc ^= std::to_integer<Uint>(in) << 8 * (sizeof(Uint)-1);
  for (int i = 0; i != 8; ++i)
    crc = (crc << 1) ^ (CRC_MASK_WORD(crc) & Poly);
  return crc;
} // CrcUpdate MsbFirst

template<std::unsigned_integral Uint, Uint Poly, CrcDir Dir>
requires (Dir == CrcDir::LsbFirst)
constexpr Uint CrcUpdate(Uint crc, std::byte in) {
  using Int = std::make_signed_t<Uint>;
  static constexpr auto Rpoly = Reflect(Poly);
  [[maybe_unused]] constexpr auto Shift = 8 * sizeof(Uint) - 1;
  crc ^= std::to_integer<Uint>(in);
  for (int i = 0; i != 8; ++i)
    crc = (crc >> 1) ^ (CRC_MASK_WORD(crc<<Shift) & Rpoly);
  return crc;
} // CrcUpdate LsbFirst

#undef CRC_MASK_WORD

} // tjg

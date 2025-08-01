#pragma once

#include "CrcCompute.h"
#include "Integer.h"

#include <span>
#include <cstdint>
#include <cstddef>

namespace tjg {

template<std::size_t Bits, uint_t<Bits>::least Poly, CrcDir Dir, int Slices=-1>
class CrcEngine {
public:
  using CrcType = uint_t<Bits>::least;
  static constexpr auto    bits = Bits;
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

  [[nodiscard]] constexpr CrcType value() const noexcept {
    if constexpr (Dir == CrcDir::MsbFirst)
      return (_crc >> Shift) ^ _xor;
    else
      return _crc ^ _xor;
  }

  constexpr CrcEngine(CrcType init_, CrcType xor_) noexcept
    : _init{Init(init_)} , _xor{xor_} , _crc{_init} { }

  constexpr void update(std::byte b) noexcept
    { _crc = CrcCompute<CrcType, Poly<<Shift, Dir, Slices>(_crc, b); }

  constexpr void update(std::span<const std::byte> buf) noexcept
    { _crc = CrcCompute<CrcType, Poly<<Shift, Dir, Slices>(_crc, buf); }
}; // CrcEngine

} // tjg

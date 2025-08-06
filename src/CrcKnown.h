#pragma once

#include "CrcEngine.h"

#include <concepts>
#include <utility>

namespace tjg {

template<class Traits_, std::size_t Slices_ = 8>
struct CrcKnown
  : public CrcEngine<Traits_::Bits,
                     Traits_::Poly,
                     Traits_::ReflectIn ? CrcDir::LsbFirst : CrcDir::MsbFirst,
                     Slices_>
{
  using Traits = Traits_;
  static constexpr auto Slices = Slices_;
  static constexpr auto Bits = Traits::Bits;
  static constexpr auto Poly = Traits::Poly;
  static constexpr auto Dir  = Traits_::ReflectIn ? CrcDir::LsbFirst
                                                  : CrcDir::MsbFirst;
  using Base = CrcEngine<Bits, Poly, Dir, Slices>;
  using CrcType = Base::CrcType;

  static constexpr auto Name  = Traits::Name;
  static constexpr auto Check = Traits::Check;

  constexpr CrcKnown() noexcept : Base{Traits::Init, Traits::XorOut} { }

  [[nodiscard]] constexpr CrcType value() const noexcept {
    if constexpr (Traits::ReflectIn == Traits::ReflectOut) {
      return Base::value();
    } else {
      constexpr auto Shift = 8 * sizeof(CrcType) - Traits::Bits;
      return Reflect(Base::value()) >> Shift;
    }
  }

}; // CrcKnown

} // tjg

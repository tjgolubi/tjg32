#pragma once

#include "CrcEngine.h"

#include <concepts>
#include <utility>

namespace tjg {

template<class Traits>
struct CrcKnown
  : public CrcEngine<Traits::Bits,
                     Traits::Poly,
                     Traits::ReflectIn ? CrcDir::LsbFirst : CrcDir::MsbFirst,
                     Traits::Slices>
{
  using Base =
    CrcEngine<Traits::Bits,
              Traits::Poly,
              Traits::ReflectIn ? CrcDir::LsbFirst : CrcDir::MsbFirst,
              Traits::Slices>;

  using TraitsType = Traits;
  using CrcType    = Base::CrcType;
  static_assert(std::is_same_v<CrcType, typename Traits::CrcType>);

  static constexpr auto Name  = Traits::Name;
  static constexpr auto Check = Traits::Check;

  constexpr CrcKnown() noexcept
    : Base{Traits::Init, Traits::XorOut}
    { }

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

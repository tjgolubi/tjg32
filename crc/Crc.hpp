#pragma once

#include "crc/CrcDetail.hpp"

#include "tjg/Integer.hpp"
#include "tjg/Reflect.hpp"

#include <ranges>

namespace tjg::crc {

constexpr std::size_t DefaultSlices = 1;
constexpr std::size_t MaxSlices = 8;

template<typename T>
concept TrivialByte = std::is_trivially_copyable_v<std::remove_cv_t<T>>
                   && sizeof(T) == 1;

template<class R>
concept ContiguousByteRange = std::ranges::contiguous_range<R>
                           && std::ranges::sized_range<R>
                           && TrivialByte<std::ranges::range_value_t<R>>;

template<std::size_t Bits_, uint_t<Bits_>::least Poly_, Endian Dir_,
         std::size_t Slices_ = DefaultSlices>
requires ((Bits_ >= 3 && Bits_ <= 64)
      && (Slices_==0 || Slices_==1 || Slices_==2 || Slices_==4 || Slices_==8))
class Crc {
public:
  static constexpr auto   Bits = Bits_;
  static constexpr auto   Poly = Poly_;
  static constexpr auto   Dir  = Dir_;
  static constexpr auto Slices = Slices_;

  using value_type = uint_t<Bits>::least;

protected:
  static constexpr auto CrcBits = 8 * sizeof(value_type);
  static constexpr unsigned Shift = CrcBits - Bits;

private:
  static constexpr value_type FastPoly = (Dir == Endian::MsbFirst)
                                       ? (Poly << Shift)
                                       : (IntMath::Reflect(Poly) >> Shift);
private:
  const value_type _init;
  const value_type _xor;
  value_type _crc;

  static constexpr value_type Init(value_type init) noexcept {
    if constexpr (Dir == Endian::MsbFirst)
      return static_cast<value_type>(init << Shift);
    else
      return static_cast<value_type>(IntMath::Reflect(init) >> Shift);
  } // Init

public:
  constexpr void reset() noexcept { _crc = _init; }

  [[nodiscard]]
  constexpr value_type value() const noexcept {
    if constexpr (Dir == Endian::MsbFirst)
      return (_crc >> Shift) ^ _xor;
    else
      return _crc ^ _xor;
  }

  constexpr explicit Crc(value_type init_, value_type xor_=0) noexcept
    : _init{Init(init_)} , _xor{xor_} , _crc{_init} { }

  constexpr void updateBit(bool bit) noexcept
    { _crc = detail::Compute<FastPoly, Dir>(_crc, bit); }

  constexpr void update(std::byte b) noexcept
    { _crc = detail::Compute<FastPoly, Dir, Slices>(_crc, b); }

  /// Update partial byte.
  constexpr void update(std::byte b, std::size_t bits) noexcept {
    if (bits == 0)
      return;
    if (bits >= 8) {
      update(b);
      return;
    }
    while (bits--) {
      if constexpr (Dir == Endian::MsbFirst) {
        updateBit(static_cast<bool>(b & std::byte{0x80}));
        b <<= 1;
      } else {
        updateBit(static_cast<bool>(b & std::byte{0x01}));
        b >>= 1;
      }
    }
  } // update

  constexpr void update(std::span<const std::byte> buf) noexcept
    { _crc = detail::Compute<FastPoly, Dir, Slices>(_crc, buf); }

  constexpr void update(const void* buf, std::size_t size) noexcept
    { update(std::span{static_cast<const std::byte*>(buf), size}); }

  // Contiguous ranges.
  template<ContiguousByteRange R>
  constexpr void update(const R& r) noexcept
    { update(std::ranges::data(r), std::ranges::size(r)); }

  constexpr operator value_type() const noexcept { return value(); }

  constexpr Crc& operator()(std::span<const std::byte> buf) noexcept
    { update(buf); return *this; }

  constexpr Crc& operator()(std::byte b) noexcept { update(b); return *this; }
}; // Crc

} // tjg::crc

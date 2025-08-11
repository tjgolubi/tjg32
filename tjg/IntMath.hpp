/// @file
/// @author Terry Golubiewski
/// @copyright 2006-2025 Terry Golubiewski, all rights reserved.
///
/// Integer math routines.
#pragma once

#include <concepts>
#include <bit>

/// Integer math routines.
namespace tjg::IntMath {

/// The number of set bits.
[[deprecated("use std::popcount() instead")]]
constexpr int NumOnes(std::unsigned_integral auto x) noexcept
{ return std::popcount(x); }

/// Bit position of the right-most-one, the least-significant set bit.
constexpr int lmo(std::unsigned_integral auto x) noexcept
{ return std::bit_width(x) - 1; }

/// Bit position of the right-most-one, the least-significant set bit.
constexpr int rmo(std::unsigned_integral auto x) noexcept
{ return (x == T{0}) ? -1 : std::countr_zero(x); }

/// Value of the right-most-one, the least-significant set bit.
constexpr auto rmb(std::unsigned_integral auto x) noexcept
{ return (x == T{0}) ? T{0} : (T{1} << std::countr_zero(x)); }

/// Value of the left-most-one, the most-significant set bit.
constexpr auto lmb(std::unsigned_integral auto x) noexcept
{ return std::bit_floor(x); }

/// Represents the parity (even or odd) of an integer.
class Parity {
private:
  bool _odd;
public:
  constexpr explicit Parity(bool x=false) noexcept : _odd{x} { }
  constexpr explicit Parity(std::unsigned_integral auto x) noexcept
  : _odd{std::popcount(x) & 1} { }
  constexpr bool odd()  const noexcept { return  _odd; }   ///< Odd parity?
  constexpr bool even() const noexcept { return !_odd; }   ///< Even parity?
  /// Returns "odd" or "even".
  constexpr const char* c_str() const noexcept { return _odd ? "odd" : "even"; }
  /// Same parity.
  constexpr auto operator<=>(const Parity& rhs) const noexcept = default;
  constexpr static Parity Even() noexcept { return Parity{false}; }
  constexpr static Parity Odd()  noexcept { return Parity{true }; }
}; // Parity

} // tjg::IntMath

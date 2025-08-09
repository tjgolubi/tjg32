/// @file
/// @brief Integer math routines.
/// @author Terry Golubiewski
/// @copyright 2006-2025 Terry Golubiewski, all rights reserved.
#pragma once

#include <concepts>
#include <array>
#include <bit>
#include <type_traits>
#include <memory>
#include <utility>
#include <cstddef>
#include <cstdint>

/// Integer math routines.
namespace tjg::IntMath {

template<std::unsigned_integral T>
constexpr int NumOnes(T x) noexcept { return std::popcount(x); }

template<std::unsigned_integral T>
constexpr int lmo(T x) noexcept { return std::bit_width(x) - 1; }

#if 0

/// @internal
namespace detail {

using NumBitsTable = std::array<std::uint8_t, 256>;
using LmoTable     = std::array<std::int8_t , 256>;

consteval NumBitsTable GenerateNumBits() {
  auto table = NumBitsTable{};
  for (unsigned i = 0; i != std::ssize(table); ++i)
    table[i] = std::popcount(i);
  return table;
}

consteval LmoTable GenerateLmoTable() {
  auto table = LmoTable{};
  table[0] = std::int8_t{-1};
  table[1] = std::int8_t{0};
  table[2] = table[3] = std::int8_t{1};
  auto i = 4;
  auto j = std::int8_t{2};
  for (auto top = 0x08; top <= 256; top <<= 1, ++j)
  {
    while (i < top)
      table[i++] = j;
  }
  return table;
} // GenerateLmoTable

} // detail

constexpr int NumOnes(std::uint8_t x) noexcept {
  static constexpr auto Table = detail::GenerateNumBits();
  return Table[x];
}

constexpr int lmo(std::uint8_t x) noexcept {
  static constexpr auto Table = detail::GenerateLmoTable();
  return Table[x];
}

namespace detail {

template<std::size_t N>
struct UnrollBuf {
  static constexpr int PopCount(const std::uint8_t* p) noexcept
    { return NumOnes(*p) + UnrollBuf<N-1>::PopCount(p+1); }

  static constexpr int Lmo(const std::uint8_t* p) noexcept {
    if (*p != 0)
      return 8 * (N-1) + lmo(*p);
    if constexpr (std::endian::native == std::endian::big)
      return UnrollBuf<N-1>::Lmo(p+1);
    else
      return UnrollBuf<N-1>::Lmo(p-1);
  } // Lmo

}; // UnrollBuf

template<>
struct UnrollBuf<1> {
  static constexpr int PopCount(const std::uint8_t* p) noexcept
    { return NumOnes(*p); }
  static constexpr int Lmo(const std::uint8_t* p) noexcept
    { return lmo(*p); }
}; // UnrollBuf

template<>
struct UnrollBuf<0> {
  static constexpr int PopCount(const std::uint8_t*) noexcept { return 0; }
  static constexpr int Lmo(const std::uint8_t*) noexcept { return -1; }
}; // UnrollBuf

template<std::size_t N, bool = (N <= 8)>
struct BufDispatcher {
  static constexpr int PopCount(const void* p) noexcept
    { return UnrollBuf<N>::PopCount(static_cast<const std::uint8_t*>(p)); }

  static constexpr int Lmo(const void* p) noexcept {
    if constexpr (std::endian::native == std::endian::big)
      return UnrollBuf<N>::Lmo(static_cast<const std::uint8_t*>(p));
    else
      return UnrollBuf<N>::Lmo(static_cast<const std::uint8_t*>(p) + N-1);
  } // Lmo

}; // BufDispatcher

template<std::size_t N>
struct BufDispatcher<N, false> {

  static constexpr int PopCount(const void* p) noexcept {
    auto cp = static_cast<const std::uint8_t*>(p);
    int sum = NumOnes(*cp);
    for (int i=1; i!=N; ++i)
      sum += NumOnes(cp[i]);
    return sum;
  } // NumOnes

  static constexpr int Lmo(const void* p) noexcept {
    if constexpr (std::endian::native == std::endian::big) {
      auto cp = static_cast<const std::uint8_t*>(p);
      for (int i=N; --i >= 0; ++cp) {
        if (*cp != 0)
          return 8 * i + lmo(*cp);
      }
    } else {
      auto cp = static_cast<const std::uint8_t*>(p) + N-1;
      for (int i=N; --i >= 0; --cp) {
        if (*cp != 0)
          return 8 * i + lmo(*cp);
      }
    }
    return -1;
  } // Lmo

}; // BufDispatcher sizeof(T) > 8

template<std::unsigned_integral T>
struct Dispatcher {
  static constexpr int PopCount(T x) noexcept
    { return BufDispatcher<sizeof(T)>::PopCount(std::addressof(x)); }

  static constexpr int Lmo(T x) noexcept
    { return BufDispatcher<sizeof(T)>::Lmo(std::addressof(x)); }
}; // Dispatcher

} // detail

/// Convert argument to an unsigned integral value.
template<std::integral T>
constexpr std::make_unsigned_t<T> unsigned_convert(T x)
  { return static_cast<std::make_unsigned_t<T>>(x); }

/// Counts the number of set bits in an integer.
template<std::unsigned_integral T>
constexpr int NumOnes(T x) noexcept
{ return detail::Dispatcher<T>::PopCount(x); }

/// Bit position of the left-most-one, the most-significant set bit.
template<std::unsigned_integral T>
constexpr int lmo(T x) noexcept { return detail::Dispatcher<T>::Lmo(x); }

#endif

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4146) // unary minus of unsigned is ok.
#endif

/// Value of the right-most-one, the least-significant set bit.
template<std::unsigned_integral T>
constexpr T rmb(T x) noexcept { return (x & -x); }

#ifdef _MSC_VER
#pragma warning(pop)
#endif

/// Bit position of the right-most-one, the least-significant set bit.
template<std::unsigned_integral T>
constexpr int rmo(T x) noexcept { return lmo(rmb(x)); }

/// Value of the left-most-one, the most-significant set bit.
template<std::unsigned_integral T>
constexpr T lmb(T x) noexcept
{ return (x == T{0}) ? T{0} : (T{1} << lmo(x)); }

/// Value of least-significant-bit of an integer (x & 1).
template<std::unsigned_integral T>
constexpr T lsb(T x) noexcept { return x & T{1}; }

/// Value of most-significant-bit of an integer.
template<std::unsigned_integral T>
constexpr T msb(T x) noexcept { return x & (T{1} << (8 * sizeof(T) - 1)); }

/// Represents the parity (even or odd) of an integer.
class Parity {
private:
  bool _odd;
public:
  constexpr Parity() noexcept : _odd{false} { } // default is even parity
  constexpr explicit Parity(bool x) noexcept : _odd{x} { }
  template<std::unsigned_integral T>
  constexpr explicit Parity(T x) noexcept : _odd{NumOnes(x) & 1} { }
  constexpr bool odd()  const noexcept { return  _odd; }   ///< Odd parity?
  constexpr bool even() const noexcept { return !_odd; }   ///< Even parity?
  /// Returns "odd" or "even".
  constexpr const char* c_str() const noexcept { return _odd ? "odd" : "even"; }
  /// Same parity.
  constexpr auto operator<=>(const Parity& rhs) const noexcept = default;
  constexpr static Parity Even() noexcept { return Parity(false); }
  constexpr static Parity Odd()  noexcept { return Parity(true ); }
}; // Parity

} // tjg::IntMath

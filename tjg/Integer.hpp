/// @file
/// @copyright 2025 Terry Golubiewski, all rights reserved.
/// @author Terry Golubiewski
/// Provides int_t<Bits> and uint_t<Bits>.

#pragma once
#include <limits>
#include <cstdint>
#include <cstddef>

namespace tjg {

using std::uint8_t;
using std::uint16_t;
using std::uint32_t;
using std::uint64_t;

using std::int8_t;
using std::int16_t;
using std::int32_t;
using std::int64_t;

#if defined(__SIZEOF_INT128__)
#define TJG_HAS_INT128 1
using uint128_t = unsigned __int128;
using int128_t  = signed   __int128;
constexpr U128(uint64_t hi, uint64_t lo) noexcept
  { return uint128_t{hi} << 64 | uint128_t{lo}; }
constexpr I128(int64_t hi, int64_t lo) noexcept
  { return int128_t(U128((hi), uint64_t(lo))); }
#endif

template<typename T>
struct int_fast_t {
  using fast = T;
  using type = fast;
};

/// @internal
namespace detail {

constexpr int Index(std::size_t Bits) noexcept
{ return (Bits > 8) + (Bits > 16) + (Bits > 32) + (Bits > 64); }

template<int N>
struct uint_least_helper;

template<>
struct uint_least_helper<0> {
  using least = uint8_t;
};

template<>
struct uint_least_helper<1> {
  using least = uint16_t;
};

template<>
struct uint_least_helper<2> {
  using least = uint32_t;
};

template<>
struct uint_least_helper<3> {
  using least = uint64_t;
};

#if defined(TJG_HAS_INT128)
template<>
struct uint_least_helper<4> {
  using least = uint128_t;
};
#endif

} // detail

template<std::size_t Bits>
requires (Bits > 0 && Bits <= 128)
struct uint_t {
  using least = detail::uint_least_helper<detail::Index(Bits)>::least;
  using fast  = int_fast_t<least>::fast;
};

/// @internal
namespace detail {

template<int N>
struct int_least_helper;

template<>
struct int_least_helper<0> {
  using least = int8_t;
}; // int_least_helper

template<>
struct int_least_helper<1> {
  using least = int16_t;
}; // int_least_helper

template<>
struct int_least_helper<2> {
  using least = int32_t;
}; // int_least_helper

template<>
struct int_least_helper<3> {
  using least = int64_t;
}; // int_least_helper

#if defined(TJG_HAS_INT128)
template<>
struct int_least_helper<4> {
  using least = int128_t;
}; // int_least_helper
#endif

} // detail

template<std::size_t Bits>
requires (Bits > 0 && Bits <= 128)
struct int_t {
  using least = detail::int_least_helper<detail::Index(Bits)>::least;
  using fast  = int_fast_t<least>::fast;
};

template<std::size_t Bit>
struct high_bit_mask_t {
  using least = uint_t<Bit+1>::least;
  using fast  = uint_t<Bit+1>::fast;
  static constexpr auto high_bit      = least(least{1u} << Bit);
  static constexpr auto high_big_fast = fast ( fast{1u} << Bit);
  static constexpr auto bit_position  = Bit;
}; // high_bit_mask_t

template<std::size_t Bits>
struct low_bits_mask_t {
  using least = uint_t<Bits>::least;
  using fast  = uint_t<Bits>::fast;
  static constexpr auto sig_bits      = least(~(least(~least{0u}) << Bits));
  static constexpr auto sig_bits_fast = fast{sig_bits};
  static constexpr auto bit_count     = Bits;
}; // low_bits_mask_t

#define TJG_LOW_BITS_MASK_SPECIALIZE(Type) \
  template<> struct low_bits_mask_t<std::numeric_limits<Type>::digits> { \
    using limits_type = std::numeric_limits<Type>;                       \
    using least = uint_t<limits_type::digits>::least;                    \
    using fast  = uint_t<limits_type::digits>::fast;                     \
    static constexpr auto sig_bits      = least(~least{0u});             \
    static constexpr auto sig_bits_fast = fast{sig_bits};                \
    static constexpr auto bit_count = limits_type::digits;               \
  }

TJG_LOW_BITS_MASK_SPECIALIZE(uint8_t);
TJG_LOW_BITS_MASK_SPECIALIZE(uint16_t);
TJG_LOW_BITS_MASK_SPECIALIZE(uint32_t);
TJG_LOW_BITS_MASK_SPECIALIZE(uint64_t);
#if defined(TJG_HAS_INT128)
TJG_LOW_BITS_MASK_SPECIALIZE(uint128_t);
#endif

#undef TJG_LOW_BITS_MASK_SPECIALIZE

} // tjg

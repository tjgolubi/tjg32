/// @file
/// @copyright 2025 Terry Golubiewski, all rights reserved.
/// @author Terry Golubiewski
/// Reverse (reflect) bits in an integer.

#pragma once
#include <tjg/Integer.hpp>
#include <limits>
#include <utility>
#include <cstdint>
#include <cstddef>

namespace tjg {

#if defined(__clang__) && __has_builtin(__builtin_bitreverse64)

constexpr uint8_t bit_reverse(uint8_t x) noexcept
  {  return __builtin_bitreverse8(x); }

constexpr uint16_t bit_reverse(uint16_t x) noexcept
  {  return __builtin_bitreverse16(x); }

constexpr uint32_t bit_reverse(uint32_t x) noexcept
  {  return __builtin_bitreverse32(x); }

constexpr uint64_t bit_reverse(uint64_t x) noexcept
  {  return __builtin_bitreverse64(x); }

#if defined(__SIZEOF_INT128__)

#if defined(__clang__) && __has_builtin(__builtin_bitreverse128)

constexpr uint128_t bit_reverse(uint128_t x) noexcept
  {  return __builtin_bitreverse128(x); }

#else

constexpr uint128_t bit_reverse(uint128_t x) noexcept {
  auto hi = static_cast<uint64_t>(x >> 64);
  auto lo = static_cast<uint64_t>(x);
  return (uint128_t{bit_reverse(lo)} << 64) | bit_reverse(hi);
}

#endif // __bultin_bitreverse128
#endif // uint128_t

#else

namespace detail_bit_reverse {

template<std::unsigned_integral T, std::size_t Bits,
         std::size_t N = std::numeric_limits<T>::digits - 2 * Bits>
constexpr T Mask() noexcept {
  constexpr auto M = T{low_bits_mask_t<Bits>::sig_bits};
  if constexpr (N == 0)
    return M;
  else
    return T{(M << N) | Mask<T, Bits, N - 2 * Bits>()};
} // Mask

template<std::unsigned_integral T, std::size_t Bits>
constexpr T Term(T x) noexcept {
  constexpr auto K = Mask<T, Bits>();
  return ((x & K) << Bits) | ((x >> Bits) & K);
} // Term

template<std::unsigned_integral T,
         std::size_t Bits = std::numeric_limits<T>::digits/2>
constexpr T BitReverse(T x) noexcept {
  if constexpr (Bits == 1)
    return Term<T, 1>(x);
  else
    return BitReverse<T, Bits/2>(Term<T, Bits>(x));
}

} // detail_bit_reverse

template<std::unsigned_integral T>
constexpr T bit_reverse(T x) noexcept {
  return detail_bit_reverse::BitReverse(x);
} // bit_reverse

#endif // clang has builtins

constexpr std::byte bit_reverse(std::byte x) noexcept
  { return std::byte{bit_reverse(std::to_integer<uint8_t>(x))}; }

} // tjg

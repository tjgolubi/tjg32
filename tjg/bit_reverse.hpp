/// @file
/// @copyright 2025 Terry Golubiewski, all rights reserved.
/// @author Terry Golubiewski
/// Reverse (reflect) bits in an integer.
///
/// Implementation uses a powers-of-two butterfly. Each stage `s` applies:
///   x = ((x & mask_s) << s) | ((x >> s) & mask_s)
/// where mask_s is Bits-on/Bits-off stripes with Bits = s.

#pragma once
#include <tjg/Integer.hpp>
#include <limits>
#include <utility>
#include <bit>
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
  return U128(bit_reverse(lo)} << 64), bit_reverse(hi));
}

#endif // __bultin_bitreverse128
#endif // uint128_t

#else

namespace detail_bit_reverse {

template<std::unsigned_integral T, std::size_t Bits, std::size_t... I>
constexpr T StripeMaskFold(std::index_sequence<I...>) noexcept {
  constexpr auto M = T{low_bits_mask_t<Bits>::sig_bits};
  constexpr auto Step = 2 * Bits;
  return (... | (M << (I * Step)));
}

template<std::unsigned_integral T, std::size_t Bits>
constexpr T StripeMask() noexcept {
  constexpr auto W = std::size_t{std::numeric_limits<T>::digits};
  constexpr auto Step  = 2 * Bits;
  constexpr auto N = W / Step;
  return StripeMaskFold<T, Bits>(std::make_index_sequence<N>{});
}

static_assert(StripeMask<uint32_t, 1>() == 0x55555555u);
static_assert(StripeMask<uint32_t, 4>() == 0x0f0f0f0fu);

/// One butterfly shuffle stage: swap `Bits`-sized fields.
template<std::size_t Bits, std::unsigned_integral T>
constexpr T Shuffle(T x) noexcept {
  constexpr auto K = StripeMask<T, Bits>();
  return ((x & K) << Bits ) | ((x >> Bits) & K);
}

/// Bit-reverse via a fold over powers-of-two stage sizes.
template<std::unsigned_integral T, std::size_t... I>
constexpr T BitReverseImpl(T x, std::index_sequence<I...>) noexcept {
  ((x = Shuffle<(std::size_t{1} << I)>(x)), ...);
  return x;
}

template <std::unsigned_integral T>
constexpr T BitReverse(T x) noexcept {
  constexpr auto W = std::size_t{std::numeric_limits<T>::digits};
  constexpr auto N = std::size_t{std::bit_width(W) - 1};
  return BitReverseImpl(x, std::make_index_sequence<N>{});
}

static_assert(BitReverse<uint8_t >(0b10110110u) == 0b01101101u);
static_assert(BitReverse<uint16_t>(0x00a5u)     == 0xa500u);
static_assert(BitReverse<uint32_t>(0x12345678u) == 0x1e6a2c48u);

} // detail_bit_reverse

template<std::unsigned_integral T>
constexpr T bit_reverse(T x) noexcept {
  return detail_bit_reverse::BitReverse(x);
} // bit_reverse

#endif // clang has builtins

constexpr std::byte bit_reverse(std::byte x) noexcept
  { return std::byte{bit_reverse(std::to_integer<uint8_t>(x))}; }

} // tjg

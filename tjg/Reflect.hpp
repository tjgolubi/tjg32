/// @file
/// @copyright 2025 Terry Golubiewski, all rights reserved.
/// @author Terry Golubiewski
/// Reflect (reverse) bits in an integer.

#pragma once
#include <cstdint>
#include <cstddef>

namespace tjg::IntMath {

constexpr std::uint8_t Reflect(std::uint8_t x) noexcept {
  x = ((x & 0x55) << 1) | ((x & 0xaa) >> 1);
  x = ((x & 0x33) << 2) | ((x & 0xcc) >> 2);
  x = ((x & 0x0f) << 4) | ((x & 0xf0) >> 4);
  return x;
} // Reflect

constexpr std::byte Reflect(std::byte x) noexcept
{ return std::byte{Reflect(std::to_integer<std::uint8_t>(x))}; }

constexpr std::uint16_t Reflect(std::uint16_t x) noexcept {
  x = ((x & 0x5555) << 1) | ((x & 0xaaaa) >> 1);
  x = ((x & 0x3333) << 2) | ((x & 0xcccc) >> 2);
  x = ((x & 0x0f0f) << 4) | ((x & 0xf0f0) >> 4);
  x = ((x & 0x00ff) << 8) | ((x & 0xff00) >> 8);
  return x;
} // Reflect

constexpr std::uint32_t Reflect(std::uint32_t x) noexcept {
  x = ((x & 0x55555555) << 1) | ((x & 0xaaaaaaaa) >> 1);
  x = ((x & 0x33333333) << 2) | ((x & 0xcccccccc) >> 2);
  x = ((x & 0x0f0f0f0f) << 4) | ((x & 0xf0f0f0f0) >> 4);
  x = ((x & 0x00ff00ff) << 8) | ((x & 0xff00ff00) >> 8);
  x = ((x & 0x0000ffff) <<16) | ((x & 0xffff0000) >>16);
  return x;
} // Reflect

constexpr std::uint64_t Reflect(std::uint64_t x) noexcept {
  x = ((x & 0x5555555555555555) << 1) | ((x & 0xaaaaaaaaaaaaaaaa) >> 1);
  x = ((x & 0x3333333333333333) << 2) | ((x & 0xcccccccccccccccc) >> 2);
  x = ((x & 0x0f0f0f0f0f0f0f0f) << 4) | ((x & 0xf0f0f0f0f0f0f0f0) >> 4);
  x = ((x & 0x00ff00ff00ff00ff) << 8) | ((x & 0xff00ff00ff00ff00) >> 8);
  x = ((x & 0x0000ffff0000ffff) <<16) | ((x & 0xffff0000ffff0000) >>16);
  x = ((x & 0x00000000ffffffff) <<32) | ((x & 0xffffffff00000000) >>32);
  return x;
} // Reflect

#if defined(__SIZEOF_INT128__)

using uint128_t = unsigned __int128;

constexpr uint128_t U128(std::uint64_t hi, std::uint64_t lo) noexcept
  { return (uint128_t{hi} << 64) | uint128_t{lo}; }

constexpr uint128_t Reflect(uint128_t x) noexcept {
  auto hi = Reflect(std::uint64_t(x >> 64));
  auto lo = Reflect(std::uint64_t(x));
  return U128(lo, hi);
} // Reflect

#endif

} // tjg::IntMath

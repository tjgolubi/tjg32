#pragma once

#include "CrcTable.h"
#include "CrcUpdate.h"
#include "Integer.h"

#include <gsl/gsl>

#include <span>
#include <concepts>
#include <utility>
#include <bit>
#include <cstdint>
#include <cstddef>

#ifndef TJG_DEBUG_ENDIAN
#define TJG_IS_LITTLE_ENDIAN (std::endian::native == std::endian::little)
#else
#define TJG_IS_LITTLE_ENDIAN (std::endian::native == std::endian::big)
#endif

namespace tjg {

namespace detail {

inline auto DebugByteSwap(auto n) noexcept {
#ifdef TJG_DEBUG_ENDIAN
  return std::byteswap(n);
#else
  return n;
#endif
} // DebugByteSwap

template<int S, std::unsigned_integral U>
requires (S > 0 && S < sizeof(U))
constexpr U Lsh(U x) noexcept { return (x << (8 * S)); }

template<int S, std::unsigned_integral U>
requires (S == 0)
constexpr U Lsh(U x) noexcept { return x; }

template<int S, std::unsigned_integral U>
requires (S < 0 || S >= sizeof(U))
constexpr U Lsh(U) noexcept { return U{0}; }

template<int S, std::unsigned_integral U>
requires (S > 0 && S < sizeof(U))
constexpr U Rsh(U x) noexcept { return (x >> (8 * S)); }

template<int S, std::unsigned_integral U>
requires (S == 0)
constexpr U Rsh(U x) noexcept { return x; }

template<int S, std::unsigned_integral U>
requires (S < 0 || S >= sizeof(U))
constexpr U Rsh(U) noexcept { return U{0}; }

template<std::unsigned_integral auto Poly, CrcDir Dir>
auto CrcSlice(auto crc, std::uint8_t byte) noexcept {
  using std::uint8_t;
  using Uint = decltype(crc);
  static constexpr const auto& Table = CrcTable<Uint, Poly, Dir, 0>::Get();
  if (Dir == CrcDir::LsbFirst)
    crc = Rsh<1>(crc) ^ Table[byte ^ (uint8_t) crc];
  else
    crc = Lsh<1>(crc) ^ Table[byte ^ (uint8_t) Rsh<sizeof(Uint)-1>(crc)];
  return crc;
} // CrcSlice

template<std::unsigned_integral Uint, Uint Poly, CrcDir Dir, std::size_t Slice>
Uint CrcTerm(Uint crc, auto word) noexcept {
  using std::uint8_t;
  using Word = decltype(word);
  static constexpr const auto& Table = CrcTable<Uint, Poly, Dir, Slice>::Get();
  static constexpr int S = Slice;
  static constexpr int C = sizeof(Uint);
  static constexpr int N = sizeof(Word) - 1;
  static constexpr int X = (Dir == CrcDir::LsbFirst) ? (N-S) : ((C-1) - (N-S));
  static constexpr int W = (TJG_IS_LITTLE_ENDIAN) ? (N-Slice) : Slice;
  return Table[(uint8_t) Rsh<W>(word) ^ (uint8_t) Rsh<X>(crc)];
}

template<std::unsigned_integral auto Poly, CrcDir Dir, std::size_t... SliceVals>
auto CrcSliceImpl(auto crc, const auto* buf, std::size_t len,
                  std::index_sequence<SliceVals...>) noexcept
{
  using Uint = decltype(crc);
  using Word = std::remove_cvref_t<decltype(*buf)>;
  static constexpr int W = sizeof(Word);
  Expects(reinterpret_cast<std::uintptr_t>(buf) % alignof(Word) == 0);
  while (len--) {
    auto n = DebugByteSwap(*buf++);
    crc = ((Dir == CrcDir::LsbFirst) ? Rsh<W>(crc) : Lsh<W>(crc))
        ^ (CrcTerm<Uint, Poly, Dir, SliceVals>(crc, n) ^ ...);
  }
  return crc;
} // CrcSliceImpl

template<std::unsigned_integral auto Poly, CrcDir Dir>
auto CrcSlice(auto crc, const auto* buf, std::size_t len) noexcept {
  using Seq = std::make_index_sequence<sizeof(*buf)>;
  return CrcSliceImpl<Poly, Dir>(crc, buf, len, Seq{});
}

} // detail

// Poly must already be reflected for LsbFirst.
template<std::unsigned_integral auto Poly, CrcDir Dir, std::size_t Slices = 1>
requires (Slices > 0)
inline auto CrcCompute(std::unsigned_integral auto crc, std::byte b) noexcept
{ return detail::CrcSlice<Poly, Dir>(crc, std::to_integer<std::uint8_t>(b)); }

// Poly must already be reflected for LsbFirst.
template<std::unsigned_integral auto Poly, CrcDir Dir, std::size_t Slices = 1>
requires (Slices == 0)
inline auto CrcCompute(std::unsigned_integral auto crc, std::byte b) noexcept
{ return CrcUpdate<Poly, Dir>(crc, b); }

// Poly must already be reflected for LsbFirst.
template<std::unsigned_integral auto Poly, CrcDir Dir, std::size_t Slices = 8>
inline auto CrcCompute(std::unsigned_integral auto crc,
                       std::span<const std::byte> buf) noexcept
  -> decltype(crc);

template<std::unsigned_integral auto Poly, CrcDir Dir, std::size_t Slices>
requires (Slices==1 || Slices==2 || Slices==4 || Slices==8)
inline auto CrcCompute(std::unsigned_integral auto crc,
                       std::span<const std::byte> buf) noexcept
{
  static_assert(sizeof(Poly) <= sizeof(crc));
  using Uint = decltype(crc);
  using Word = uint_t<8 * Slices>::least;
  auto p  = reinterpret_cast<const std::uint8_t*>(buf.data());
  auto sz = buf.size();
  if constexpr (Slices > 1) {
     auto num = static_cast<std::size_t>(
                                 reinterpret_cast<std::uintptr_t>(p) % Slices);
    if (num != 0) {
      num = Slices - num;
      crc = detail::CrcSlice<Poly, Dir>(crc, p, num);
      p  += num;
      sz -= num;
    }
  }
  auto p2  = reinterpret_cast<const Word*>(p);
  auto sz2 = sz / sizeof(Word);
  crc = detail::CrcSlice<Poly, Dir>(crc, p2, sz2);
  sz2 *= sizeof(Word);
  sz -= sz2;
  if (sz > 0) {
    p += sz2;
    crc = detail::CrcSlice<Poly, Dir>(crc, p, sz);
  }
  return crc;
} // CrcCompute

template<std::unsigned_integral auto Poly, CrcDir Dir, std::size_t Slices>
requires (Slices == 0)
inline auto CrcCompute(std::unsigned_integral auto crc,
                       std::span<const std::byte> buf) noexcept
{
  static_assert(sizeof(Poly) <= sizeof(crc));
  for (auto b: buf)
    crc = CrcUpdate<Poly, Dir>(crc, b);
  return crc;
} // CrcCompute

} // tjg

#undef TJG_IS_LITTLE_ENDIAN

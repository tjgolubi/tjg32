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

template<std::unsigned_integral Uint, Uint Poly, CrcDir Dir, int Slice>
Uint CrcTerm(Uint crc, auto word) noexcept {
  using Word = decltype(word);
  static constexpr const auto& Table = CrcTable<Uint, Poly, Dir, Slice>::Get();
  static constexpr int C = sizeof(Uint);
  static constexpr int N = sizeof(Word) - 1;
  static constexpr int X = (Dir == CrcDir::LsbFirst)
                         ? (N-Slice) : ((C-1) - (N-Slice));
  static constexpr int W = (TJG_IS_LITTLE_ENDIAN) ? (N-Slice) : Slice;
  return Table[(uint8_t) Rsh<W>(word) ^ (uint8_t) Rsh<X>(crc)];
}

template<std::unsigned_integral auto Poly, CrcDir Dir>
auto CrcSlice(std::unsigned_integral auto crc,
         const std::uint8_t* buf, std::size_t len) noexcept
  -> decltype(crc)
{
  using std::uint8_t;
  using Word = std::uint8_t;
  using Uint = decltype(crc);
  static constexpr int W = sizeof(Word);
  Expects(reinterpret_cast<std::uintptr_t>(buf) % alignof(Word) == 0);
  auto ptr = buf;
  for (std::size_t i = 0; i != len; ++i) {
    auto n = DebugByteSwap(*ptr++);
    crc = ((Dir == CrcDir::LsbFirst) ? Rsh<W>(crc) : Lsh<W>(crc))
        ^ CrcTerm<Uint, Poly, Dir, 0>(crc, n);
  }
  return crc;
} // CrcSlice

template<std::unsigned_integral auto Poly, CrcDir Dir>
auto CrcSlice(std::unsigned_integral auto crc,
              const std::uint16_t* buf, std::size_t len) noexcept
  -> decltype(crc)
{
  using std::uint8_t;
  using Word = std::uint16_t;
  using Uint = decltype(crc);
  static constexpr int W = sizeof(Word);
  Expects(reinterpret_cast<std::uintptr_t>(buf) % alignof(Word) == 0);
  auto ptr = buf;
  for (std::size_t i = 0; i != len; ++i) {
    auto n = DebugByteSwap(*ptr++);
    crc = ((Dir == CrcDir::LsbFirst) ? Rsh<W>(crc) : Lsh<W>(crc))
        ^ CrcTerm<Uint, Poly, Dir, 0>(crc, n)
        ^ CrcTerm<Uint, Poly, Dir, 1>(crc, n);
  }
  return crc;
} // CrcSlice

template<std::unsigned_integral auto Poly, CrcDir Dir>
auto CrcSlice(std::unsigned_integral auto crc,
              const std::uint32_t* buf, std::size_t len) noexcept
  -> decltype(crc)
{
  using std::uint8_t;
  using Word = std::uint32_t;
  using Uint = decltype(crc);
  static constexpr int W = sizeof(Word);
  Expects(reinterpret_cast<std::uintptr_t>(buf) % alignof(Word) == 0);
  auto ptr = buf;
  for (std::size_t i = 0; i != len; ++i) {
    auto n = DebugByteSwap(*ptr++);
    crc = ((Dir == CrcDir::LsbFirst) ? Rsh<W>(crc) : Lsh<W>(crc))
        ^ CrcTerm<Uint, Poly, Dir, 0>(crc, n)
        ^ CrcTerm<Uint, Poly, Dir, 1>(crc, n)
        ^ CrcTerm<Uint, Poly, Dir, 2>(crc, n)
        ^ CrcTerm<Uint, Poly, Dir, 3>(crc, n);
  }
  return crc;
} // CrcSlice

template<std::unsigned_integral auto Poly, CrcDir Dir>
auto CrcSlice(std::unsigned_integral auto crc,
              const std::uint64_t* buf, std::size_t len) noexcept
  -> decltype(crc)
{
  using std::uint8_t;
  using Word = std::uint64_t;
  using Uint = decltype(crc);
  static constexpr int W = sizeof(Word);
  Expects(reinterpret_cast<std::uintptr_t>(buf) % alignof(Word) == 0);
  auto ptr = buf;
  for (std::size_t i = 0; i != len; ++i) {
    auto n = DebugByteSwap(*ptr++);
    crc = ((Dir == CrcDir::LsbFirst) ? Rsh<W>(crc) : Lsh<W>(crc))
        ^ CrcTerm<Uint, Poly, Dir, 0>(crc, n)
        ^ CrcTerm<Uint, Poly, Dir, 1>(crc, n)
        ^ CrcTerm<Uint, Poly, Dir, 2>(crc, n)
        ^ CrcTerm<Uint, Poly, Dir, 3>(crc, n)
        ^ CrcTerm<Uint, Poly, Dir, 4>(crc, n)
        ^ CrcTerm<Uint, Poly, Dir, 5>(crc, n)
        ^ CrcTerm<Uint, Poly, Dir, 6>(crc, n)
        ^ CrcTerm<Uint, Poly, Dir, 7>(crc, n);
  }
  return crc;
} // CrcSlice

} // detail

// Poly must already be reflected for LsbFirst.
template<std::unsigned_integral auto Poly, CrcDir Dir, int Slices = -1>
inline auto CrcCompute(std::unsigned_integral auto crc,
                       std::span<const std::byte> buf) noexcept
  -> decltype(crc);

template<std::unsigned_integral auto Poly, CrcDir Dir, int Slices>
requires (Slices==1 || Slices==2 || Slices==4 || Slices==8)
inline auto CrcCompute(std::unsigned_integral auto crc,
                       std::span<const std::byte> buf) noexcept
  -> decltype(crc)
{
  using Uint = decltype(crc);
  static_assert(sizeof(Poly) <= sizeof(Uint));
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

template<std::unsigned_integral auto Poly, CrcDir Dir, int Slices>
requires (Slices == -1)
inline auto CrcCompute(std::unsigned_integral auto crc,
                       std::span<const std::byte> buf) noexcept
  -> decltype(crc)
{
  auto p  = reinterpret_cast<const uint8_t*>(buf.data());
  auto sz = buf.size();
  /// @note To disable slicing on platforms where multi-byte folding
  ///       is not beneficial, set `EnableSlicing = false`. This causes
  ///       all input to be processed using a single lookup table and
  ///       the classic Sarwate algorithm.
  constexpr bool EnableSlicing = true;
  if constexpr (EnableSlicing) {
    if (sz >= 8) {
      {
        // Align the buffer to 8-byte address.
        auto ip = reinterpret_cast<std::uintptr_t>(p);
        auto rem = ip % 8;
        if (rem != 0) {
          auto n = 8 - rem;
          crc = detail::CrcSlice<Poly, Dir>(crc, p, n);
          p  += n;
          sz -= n;
        }
      }
      if constexpr (requires { typename std::uint64_t; }) {
        if (sz >= sizeof(std::uint64_t)) {
          using Word = std::uint64_t;
          auto p2 = reinterpret_cast<const Word*>(p);
          auto sz2 = sz / sizeof(Word);
          crc = detail::CrcSlice<Poly, Dir>(crc, p2, sz2);
          sz2 *= sizeof(Word);;
          p  += sz2;
          sz -= sz2;
        }
      }
      if (sz >= sizeof(std::uint32_t)) {
        using Word = std::uint32_t;
        auto p2  = reinterpret_cast<const Word*>(p);
        auto sz2 = sz / sizeof(Word);
        crc = detail::CrcSlice<Poly, Dir>(crc, p2, sz2);
        sz2 *= sizeof(Word);;
        p  += sz2;
        sz -= sz2;
      }
      if (sz >= sizeof(std::uint16_t)) {
        using Word = std::uint16_t;
        auto p2  = reinterpret_cast<const Word*>(p);
        auto sz2 = sz / sizeof(Word);
        crc = detail::CrcSlice<Poly, Dir>(crc, p2, sz2);
        sz2 *= sizeof(Word);;
        p  += sz2;
        sz -= sz2;
      }
    }
  }
  if (sz > 0)
    crc = detail::CrcSlice<Poly, Dir>(crc, p, sz);
  return crc;
} // CrcCompute

template<std::unsigned_integral auto Poly, CrcDir Dir, int Slices>
requires (Slices == 0)
inline auto CrcCompute(std::unsigned_integral auto crc,
                       std::span<const std::byte> buf) noexcept
  -> decltype(crc)
{
  for (auto b: buf)
    crc = CrcUpdate<Poly, Dir>(crc, b);
  return crc;
} // CrcCompute

} // tjg

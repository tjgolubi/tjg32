#pragma once

#include "CrcTable.h"
#include "CrcUpdate.h"
#include "Integer.h"

#include <gsl/gsl>

#include <span>
#include <concepts>
#include <utility>
#include <cstdint>
#include <cstddef>

namespace tjg {

namespace detail {

template<std::unsigned_integral Uint, Uint Poly, CrcDir Dir,
         std::unsigned_integral Word, std::size_t... Is>
requires (Dir == CrcDir::LsbFirst)
constexpr Uint FoldAccumImpl(Word word, std::index_sequence<Is...>) {
  return (... ^
    CrcTable<Uint, Poly, CrcDir::LsbFirst, sizeof...(Is) - 1 - Is>::Get()
                                [static_cast<std::uint8_t>(word >> (8 * Is))]);
}

template<std::unsigned_integral Uint, Uint Poly, CrcDir Dir,
         std::unsigned_integral Word, std::size_t... Is>
requires (Dir == CrcDir::MsbFirst)
constexpr Uint FoldAccumImpl(Word word, std::index_sequence<Is...>) {
  return (... ^
    CrcTable<Uint, Poly, CrcDir::MsbFirst, Is>::Get()
                                [static_cast<std::uint8_t>(word >> (8 * Is))]);
}

template<std::unsigned_integral Uint, Uint Poly, CrcDir Dir,
         std::unsigned_integral Word, std::size_t N>
constexpr Uint FoldAccum(Word word) {
  return FoldAccumImpl<Uint, Poly, Dir, Word>(word,
                                                std::make_index_sequence<N>{});
}

template<std::unsigned_integral Uint, Uint Poly, CrcDir Dir, std::size_t Bytes>
Uint CrcSlice(Uint crc, const std::byte* buf, std::size_t len) noexcept {
  using Word = uint_t<8 * Bytes>::least;
  Expects(reinterpret_cast<std::uintptr_t>(buf) % alignof(Word) == 0);

  auto ptr = reinterpret_cast<const Word*>(buf);
  const auto num = len / Bytes;
  const auto rem = len % Bytes;
  for (std::size_t i = 0; i < num; ++i)
    crc ^= FoldAccum<Uint, Poly, Dir, Word, Bytes>(*ptr++);

  if constexpr (Bytes > 1) {
    if (rem != 0) {
      crc = CrcSlice<Uint, Poly, Dir, Bytes/2>(crc,
                                reinterpret_cast<const std::byte*>(ptr), rem);
    }
  }

  return crc;
} // CrcSlice

} // detail

template<std::unsigned_integral Uint, Uint Poly, CrcDir Dir, int Slices = -1>
inline Uint CrcCompute(Uint crc, std::span<const std::byte> buf) noexcept;

template<std::unsigned_integral Uint, Uint Poly, CrcDir Dir, int Slices>
requires (Slices==1 || Slices==2 || Slices==4 || Slices==8)
inline Uint CrcCompute(Uint crc, std::span<const std::byte> buf) noexcept {
  if constexpr (Slices > 1)
    Expects(reinterpret_cast<std::uintptr_t>(buf.data()) % Slices == 0);
  crc = detail::CrcSlice<Uint, Poly, Dir, Slices>(crc, buf.data(), buf.size());
  return crc;
} // CrcCompute

template<std::unsigned_integral Uint, Uint Poly, CrcDir Dir, int Slices>
requires (Slices == -1)
inline Uint CrcCompute(Uint crc, std::span<const std::byte> buf) noexcept {
  /// @note To disable slicing on platforms where multi-byte folding
  ///       is not beneficial, set `EnableSlicing = false`. This causes
  ///       all input to be processed using a single lookup table and
  ///       the classic Sarwate algorithm.
  constexpr bool EnableSlicing = true;

  if constexpr (EnableSlicing) {
    if constexpr (requires { typename std::uint64_t; }) {
      if (buf.size() >= 8)
        return CrcCompute<Uint, Poly, Dir, 8>(crc, buf);
    }
    if (buf.size() >= 4)
      return CrcCompute<Uint, Poly, Dir, 4>(crc, buf);
    if (buf.size() >= 2)
      return CrcCompute<Uint, Poly, Dir, 2>(crc, buf);
  }
  return CrcCompute<Uint, Poly, Dir, 1>(crc, buf);
} // CrcCompute

template<std::unsigned_integral Uint, Uint Poly, CrcDir Dir, int Slices>
requires (Slices == 0)
inline Uint CrcCompute(Uint crc, std::span<const std::byte> buf) noexcept {
  for (auto b: buf)
    crc = CrcUpdate<Uint, Poly, Dir>(crc, b);
  return crc;
} // CrcCompute

} // tjg

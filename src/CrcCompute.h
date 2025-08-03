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

template<std::unsigned_integral Uint, Uint Poly, CrcDir Dir,
         std::unsigned_integral Word, std::size_t... Is>
requires (Dir == CrcDir::LsbFirst)
constexpr Uint FoldAccumImpl(Word word, std::index_sequence<Is...>) {
  return (... ^
    CrcTable<Uint, Poly, CrcDir::LsbFirst, sizeof...(Is) - 1 - Is>::Get()
                                [(std::uint8_t)(word >> (8 * Is))]);
}

template<std::unsigned_integral Uint, Uint Poly, CrcDir Dir,
         std::unsigned_integral Word, std::size_t... Is>
requires (Dir == CrcDir::MsbFirst)
constexpr Uint FoldAccumImpl(Word word, std::index_sequence<Is...>) {
  return (... ^
    CrcTable<Uint, Poly, CrcDir::MsbFirst, Is>::Get()
                                [(std::uint8_t)(word >> (8 * Is))]);
}

template<std::unsigned_integral Uint, Uint Poly, CrcDir Dir,
         std::unsigned_integral Word, std::size_t N>
constexpr Uint FoldAccum(Word word) {
  return FoldAccumImpl<Uint, Poly, Dir, Word>(word,
                                                std::make_index_sequence<N>{});
}

template<std::unsigned_integral auto Poly, CrcDir Dir>
auto CrcSlice(std::unsigned_integral auto crc,
         const std::uint8_t* buf, std::size_t len) noexcept
  -> decltype(crc)
{
  using std::uint8_t;
  using Word = std::uint8_t;
  using Uint = decltype(crc);
  Expects(reinterpret_cast<std::uintptr_t>(buf) % alignof(Word) == 0);
  static constexpr int C = sizeof(Uint);
  static constexpr int W = sizeof(Word);
  constexpr auto Table0 = CrcTable<Uint, Poly, Dir, 0>::Get();
  auto ptr = buf;
  for (std::size_t i = 0; i != len; ++i) {
    auto n = *ptr++;
    if constexpr (Dir == CrcDir::LsbFirst)
      crc = Rsh<W>(crc) ^ Table0[(uint8_t) n ^ (uint8_t) crc];
    else
      crc = Lsh<W>(crc) ^ Table0[(uint8_t) n ^ (uint8_t) Rsh<C-1>(crc)];
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
  Expects(reinterpret_cast<std::uintptr_t>(buf) % alignof(Word) == 0);
  static constexpr int C = sizeof(Uint);
  static constexpr int W = sizeof(Word);
  constexpr auto Table0 = CrcTable<Uint, Poly, Dir, 0>::Get();
  constexpr auto Table1 = CrcTable<Uint, Poly, Dir, 1>::Get();
  auto ptr = buf;
  for (std::size_t i = 0; i != len; ++i) {
    auto n = *ptr++;
    if (Dir == CrcDir::LsbFirst) {
      if (std::endian::native == std::endian::little) {
        crc = Rsh<W>(crc)
            ^ Table1[(uint8_t) Rsh<0>(n) ^ (uint8_t) Rsh<0>(crc)]
            ^ Table0[(uint8_t) Rsh<1>(n) ^ (uint8_t) Rsh<1>(crc)];
      } else {
        crc = Rsh<W>(crc)
            ^ Table1[(uint8_t) Rsh<1>(n) ^ (uint8_t) Rsh<0>(crc)]
            ^ Table0[(uint8_t) Rsh<0>(n) ^ (uint8_t) Rsh<1>(crc)];
      }
    } else {
      if (std::endian::native == std::endian::little) {
        crc = Lsh<W>(crc)
            ^ Table1[(uint8_t) Rsh<0>(n) ^ (uint8_t) Rsh<C-1>(crc)]
            ^ Table0[(uint8_t) Rsh<1>(n) ^ (uint8_t) Rsh<C-2>(crc)];
      } else {
        crc = Lsh<W>(crc)
            ^ Table1[(uint8_t)(Rsh<1>(n) ^ (uint8_t) Rsh<C-1>(crc))]
            ^ Table0[(uint8_t)(Rsh<0>(n) ^ (uint8_t) Rsh<C-2>(crc))];
      }
    }
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
  Expects(reinterpret_cast<std::uintptr_t>(buf) % alignof(Word) == 0);
  static constexpr int C = sizeof(Uint);
  static constexpr int W = sizeof(Word);
  constexpr auto Table0 = CrcTable<Uint, Poly, Dir, 0>::Get();
  constexpr auto Table1 = CrcTable<Uint, Poly, Dir, 1>::Get();
  constexpr auto Table2 = CrcTable<Uint, Poly, Dir, 2>::Get();
  constexpr auto Table3 = CrcTable<Uint, Poly, Dir, 3>::Get();
  auto ptr = buf;
  for (std::size_t i = 0; i != len; ++i) {
    auto n = *ptr++;
    if (Dir == CrcDir::LsbFirst) {
      if (std::endian::native == std::endian::little) {
        crc = Rsh<W>(crc)
            ^ Table3[(uint8_t) Rsh<0>(n) ^ (uint8_t) Rsh<0>(crc)]
            ^ Table2[(uint8_t) Rsh<1>(n) ^ (uint8_t) Rsh<1>(crc)]
            ^ Table1[(uint8_t) Rsh<2>(n) ^ (uint8_t) Rsh<2>(crc)]
            ^ Table0[(uint8_t) Rsh<3>(n) ^ (uint8_t) Rsh<3>(crc)];
      } else {
        crc = Rsh<W>(crc)
            ^ Table3[(uint8_t) Rsh<3>(n) ^ (uint8_t) Rsh<0>(crc)]
            ^ Table2[(uint8_t) Rsh<2>(n) ^ (uint8_t) Rsh<1>(crc)]
            ^ Table1[(uint8_t) Rsh<1>(n) ^ (uint8_t) Rsh<2>(crc)]
            ^ Table0[(uint8_t) Rsh<0>(n) ^ (uint8_t) Rsh<3>(crc)];
      }
    } else {
      if (std::endian::native == std::endian::little) {
        crc = Lsh<W>(crc)
            ^ Table3[(uint8_t) Rsh<0>(n) ^ (uint8_t) Rsh<C-1>(crc)]
            ^ Table2[(uint8_t) Rsh<1>(n) ^ (uint8_t) Rsh<C-2>(crc)]
            ^ Table1[(uint8_t) Rsh<2>(n) ^ (uint8_t) Rsh<C-3>(crc)]
            ^ Table0[(uint8_t) Rsh<3>(n) ^ (uint8_t) Rsh<C-4>(crc)];
      } else {
        crc = Lsh<W>(crc)
            ^ Table3[(uint8_t) Rsh<3>(n) ^ (uint8_t) Rsh<C-1>(crc)]
            ^ Table2[(uint8_t) Rsh<2>(n) ^ (uint8_t) Rsh<C-2>(crc)]
            ^ Table1[(uint8_t) Rsh<1>(n) ^ (uint8_t) Rsh<C-3>(crc)]
            ^ Table0[(uint8_t) Rsh<0>(n) ^ (uint8_t) Rsh<C-4>(crc)];
      }
    }
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
  Expects(reinterpret_cast<std::uintptr_t>(buf) % alignof(Word) == 0);
  static constexpr int C = sizeof(Uint);
  static constexpr int W = sizeof(Word);
  constexpr auto Table0 = CrcTable<Uint, Poly, Dir, 0>::Get();
  constexpr auto Table1 = CrcTable<Uint, Poly, Dir, 1>::Get();
  constexpr auto Table2 = CrcTable<Uint, Poly, Dir, 2>::Get();
  constexpr auto Table3 = CrcTable<Uint, Poly, Dir, 3>::Get();
  constexpr auto Table4 = CrcTable<Uint, Poly, Dir, 4>::Get();
  constexpr auto Table5 = CrcTable<Uint, Poly, Dir, 5>::Get();
  constexpr auto Table6 = CrcTable<Uint, Poly, Dir, 6>::Get();
  constexpr auto Table7 = CrcTable<Uint, Poly, Dir, 7>::Get();
  auto ptr = buf;
  for (std::size_t i = 0; i != len; ++i) {
    auto n = *ptr++;
    if (Dir == CrcDir::LsbFirst) {
      if (std::endian::native == std::endian::little) {
        crc = Rsh<W>(crc)
            ^ Table7[(uint8_t) Rsh<0>(n) ^ (uint8_t) Rsh<0>(crc)]
            ^ Table6[(uint8_t) Rsh<1>(n) ^ (uint8_t) Rsh<1>(crc)]
            ^ Table5[(uint8_t) Rsh<2>(n) ^ (uint8_t) Rsh<2>(crc)]
            ^ Table4[(uint8_t) Rsh<3>(n) ^ (uint8_t) Rsh<3>(crc)]
            ^ Table3[(uint8_t) Rsh<4>(n) ^ (uint8_t) Rsh<4>(crc)]
            ^ Table2[(uint8_t) Rsh<5>(n) ^ (uint8_t) Rsh<5>(crc)]
            ^ Table1[(uint8_t) Rsh<6>(n) ^ (uint8_t) Rsh<6>(crc)]
            ^ Table0[(uint8_t) Rsh<7>(n) ^ (uint8_t) Rsh<7>(crc)];
      } else {
        crc = Rsh<W>(crc)
            ^ Table7[(uint8_t) Rsh<7>(n) ^ (uint8_t) Rsh<0>(crc)]
            ^ Table6[(uint8_t) Rsh<6>(n) ^ (uint8_t) Rsh<1>(crc)]
            ^ Table5[(uint8_t) Rsh<5>(n) ^ (uint8_t) Rsh<2>(crc)]
            ^ Table4[(uint8_t) Rsh<4>(n) ^ (uint8_t) Rsh<3>(crc)]
            ^ Table3[(uint8_t) Rsh<3>(n) ^ (uint8_t) Rsh<4>(crc)]
            ^ Table2[(uint8_t) Rsh<2>(n) ^ (uint8_t) Rsh<5>(crc)]
            ^ Table1[(uint8_t) Rsh<1>(n) ^ (uint8_t) Rsh<6>(crc)]
            ^ Table0[(uint8_t) Rsh<0>(n) ^ (uint8_t) Rsh<7>(crc)];
      }
    } else {
      if (std::endian::native == std::endian::little) {
        crc = Lsh<W>(crc)
            ^ Table7[(uint8_t) Rsh<0>(n) ^ (uint8_t) Rsh<C-1>(crc)]
            ^ Table6[(uint8_t) Rsh<1>(n) ^ (uint8_t) Rsh<C-2>(crc)]
            ^ Table5[(uint8_t) Rsh<2>(n) ^ (uint8_t) Rsh<C-3>(crc)]
            ^ Table4[(uint8_t) Rsh<3>(n) ^ (uint8_t) Rsh<C-4>(crc)]
            ^ Table3[(uint8_t) Rsh<4>(n) ^ (uint8_t) Rsh<C-5>(crc)]
            ^ Table2[(uint8_t) Rsh<5>(n) ^ (uint8_t) Rsh<C-6>(crc)]
            ^ Table1[(uint8_t) Rsh<6>(n) ^ (uint8_t) Rsh<C-7>(crc)]
            ^ Table0[(uint8_t) Rsh<7>(n) ^ (uint8_t) Rsh<C-8>(crc)];
      } else {
        crc = Lsh<W>(crc)
            ^ Table7[(uint8_t) Rsh<7>(n) ^ (uint8_t) Rsh<C-1>(crc)]
            ^ Table6[(uint8_t) Rsh<6>(n) ^ (uint8_t) Rsh<C-2>(crc)]
            ^ Table5[(uint8_t) Rsh<5>(n) ^ (uint8_t) Rsh<C-3>(crc)]
            ^ Table4[(uint8_t) Rsh<4>(n) ^ (uint8_t) Rsh<C-4>(crc)]
            ^ Table3[(uint8_t) Rsh<3>(n) ^ (uint8_t) Rsh<C-5>(crc)]
            ^ Table2[(uint8_t) Rsh<2>(n) ^ (uint8_t) Rsh<C-6>(crc)]
            ^ Table1[(uint8_t) Rsh<1>(n) ^ (uint8_t) Rsh<C-7>(crc)]
            ^ Table0[(uint8_t) Rsh<0>(n) ^ (uint8_t) Rsh<C-8>(crc)];
      }
    }
  }
  return crc;
} // CrcSlice

#if 0
template<typename Uint, Uint Poly, CrcDir Dir, std::size_t Bytes>
requires (Bytes > 2)
Uint CrcSlice(Uint crc, const std::byte* buf, std::size_t len) noexcept {
  using Word = uint_t<8 * Bytes>::least;
  Expects(reinterpret_cast<std::uintptr_t>(buf) % alignof(Word) == 0);

  auto ptr = reinterpret_cast<const Word*>(buf);
  const std::size_t num = len / Bytes;
  const std::size_t rem = len % Bytes;
  for (std::size_t i = 0; i != num; ++i)
    crc = (crc >> 8) ^ FoldAccum<Uint, Poly, Dir, Word, Bytes>(*ptr++);

  if constexpr (Bytes > 1) {
    if (rem != 0) {
      crc = CrcSlice<Uint, Poly, Dir, 1>(crc,
                                reinterpret_cast<const std::byte*>(ptr), rem);
    }
  }

  return crc;
} // CrcSlice
#endif

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
  if constexpr (Slices > 1)
    Expects(reinterpret_cast<std::uintptr_t>(buf.data()) % Slices == 0);
  static_assert(sizeof(Poly) <= sizeof(Uint));
  using Word = uint_t<8 * Slices>::least;
  auto p  = reinterpret_cast<const std::uint8_t*>(buf.data());
  auto sz = buf.size();
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
    if (sz >= sizeof(std::uint64_t)) {
      {
        // Align the buffer to 8-byte address.
        auto ip = reinterpret_cast<std::uintptr_t>(p);
        auto rem = ip % 8;
        if (rem != 0) {
          auto n = 8 - rem;
          crc = CrcSlice<Poly, Dir>(crc, p, n);
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

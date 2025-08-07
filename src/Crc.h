#pragma once

#include "../tjg/Integer.h"
#include "../tjg/Reflect.h"

#include <array>
#include <span>
#include <concepts>
#include <type_traits>
#include <cstddef>
#include <utility>
#include <bit>
#include <cstdint>
#include <cstddef>

namespace tjg::crc {

enum class Endian { LsbFirst, MsbFirst };

namespace detail {
//
// CRC_MASK_WORD evaluates to either 0 or ~0, depending on the MSB of its
// argument.  The DEBUG implementation runs faster when compiled
// with -O0 or -Og.  For all other optimization levels, the other wins.
#ifndef DEBUG
#define CRC_MASK_WORD(x) (-(Uint)((Int)(x) < Int{0}))
#else
#define CRC_MASK_WORD(x) ((Uint)((Int)(x) >> (8*sizeof(Uint)-1)))
#endif

template<std::unsigned_integral auto Poly, Endian Dir>
requires (Dir == Endian::MsbFirst)
constexpr auto Update(std::unsigned_integral auto crc, std::byte in) noexcept
  -> decltype(crc)
{
  using Uint = decltype(crc);
  using Int = std::make_signed_t<Uint>;
  crc ^= std::to_integer<Uint>(in) << 8 * (sizeof(Uint)-1);
  for (int i = 0; i != 8; ++i)
    crc = (crc << 1) ^ (CRC_MASK_WORD(crc) & Poly);
  return crc;
} // Update MsbFirst

// Poly must already be reflected.
template<std::unsigned_integral auto Poly, Endian Dir>
requires (Dir == Endian::LsbFirst)
constexpr auto Update(std::unsigned_integral auto crc, std::byte in) noexcept
  -> decltype(crc)
{
  using Uint = decltype(crc);
  using Int = std::make_signed_t<Uint>;
  constexpr auto Shift = 8 * sizeof(Uint) - 1;
  crc ^= std::to_integer<Uint>(in);
  for (int i = 0; i != 8; ++i)
    crc = (crc >> 1) ^ (CRC_MASK_WORD(crc<<Shift) & Poly);
  return crc;
} // Update LsbFirst

#undef CRC_MASK_WORD

template<std::unsigned_integral Uint, Uint Poly, Endian Dir, std::size_t Slice>
class Lookup : public std::array<Uint, 256> {
private:
  using Table = std::array<Uint, 256>;

  static consteval Table Generate() noexcept
  requires (Slice == 0 && Dir == Endian::MsbFirst)
  {
    auto table = Table{};
    using Int = std::make_signed_t<Uint>;
    static constexpr auto Shift = 8 * sizeof(Uint) - 1;
    Uint crc = Uint{1} << Shift;
    table[0] = Uint{0};
    for (unsigned i = 0x01; i != 0x100; i <<= 1) {
      crc = (crc << 1) ^ (((crc >> Shift) & 1) ? Poly : 0);
      for (unsigned j = 0; j != i; ++j)
        table[i+j] = crc ^ table[j];
    }
    return table;
  }; // Generate

  static consteval Table Generate() noexcept
  requires (Slice == 0 && Dir == Endian::LsbFirst)
  {
    auto table = Table{};
    Uint crc = Uint{1};
    table[0] = Uint{0};
    for (unsigned i = 0x80; i != 0x00; i >>= 1) {
      crc = (crc >> 1) ^ ((crc & 1) ? Poly : 0);
      for (unsigned j = 0; j < 256; j += 2 * i)
        table[i+j] = crc ^ table[j];
    }
    return table;
  }; // Generate

  static consteval Table Generate() noexcept
  requires (Slice > 0 && Slice <= 8)
  {
    auto table = Table{};
    auto& Tbl0=Lookup<Uint, Poly, Dir, 0>::Get();
    auto& Prev=Lookup<Uint, Poly, Dir, Slice-1>::Get();
    static constexpr auto Shift = 8 * sizeof(Uint) - 8;
    for (int i = 0; i != 256; ++i) {
      auto crc = Prev[i];
      if (Dir == Endian::LsbFirst)
        table[i] = (crc >> 8) ^ Tbl0[(std::uint8_t) crc];
      else
        table[i] = (crc << 8) ^ Tbl0[crc >> Shift];
    }
    return table;
  }; // Generate

  constexpr Lookup() : Table{Generate()} { }

public:
  static constexpr const Lookup& Get() noexcept {
    static constexpr auto TheTable = Lookup{};
    return TheTable;
  }
}; // Lookup

#ifndef TJG_DEBUG_ENDIAN
#define TJG_IS_LITTLE_ENDIAN (std::endian::native == std::endian::little)
#else
#define TJG_IS_LITTLE_ENDIAN (std::endian::native == std::endian::big)
#endif

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

template<std::unsigned_integral auto Poly, Endian Dir>
auto DoSlice(auto crc, std::uint8_t byte) noexcept {
  using std::uint8_t;
  using Uint = decltype(crc);
  static constexpr const auto& Table = Lookup<Uint, Poly, Dir, 0>::Get();
  if (Dir == Endian::LsbFirst)
    crc = Rsh<1>(crc) ^ Table[byte ^ (uint8_t) crc];
  else
    crc = Lsh<1>(crc) ^ Table[byte ^ (uint8_t) Rsh<sizeof(Uint)-1>(crc)];
  return crc;
} // DoSlice

template<std::unsigned_integral Uint, Uint Poly, Endian Dir, std::size_t Slice>
Uint Term(Uint crc, auto word) noexcept {
  using std::uint8_t;
  using Word = decltype(word);
  static constexpr const auto& Table = Lookup<Uint, Poly, Dir, Slice>::Get();
  static constexpr int S = Slice;
  static constexpr int C = sizeof(Uint);
  static constexpr int N = sizeof(Word) - 1;
  static constexpr int X = (Dir == Endian::LsbFirst) ? (N-S) : ((C-1) - (N-S));
  static constexpr int W = (TJG_IS_LITTLE_ENDIAN) ? (N-Slice) : Slice;
  return Table[(uint8_t) Rsh<W>(word) ^ (uint8_t) Rsh<X>(crc)];
}

template<std::unsigned_integral auto Poly, Endian Dir, std::size_t... SliceVals>
auto DoSliceImpl(auto crc, const auto* buf, std::size_t len,
                  std::index_sequence<SliceVals...>) noexcept
{
  using Uint = decltype(crc);
  using Word = std::remove_cvref_t<decltype(*buf)>;
  static constexpr int W = sizeof(Word);
  while (len--) {
    auto n = DebugByteSwap(*buf++);
    crc = ((Dir == Endian::LsbFirst) ? Rsh<W>(crc) : Lsh<W>(crc))
        ^ (Term<Uint, Poly, Dir, SliceVals>(crc, n) ^ ...);
  }
  return crc;
} // DoSliceImpl

template<std::unsigned_integral auto Poly, Endian Dir>
auto DoSlice(auto crc, const auto* buf, std::size_t len) noexcept {
  using Seq = std::make_index_sequence<sizeof(*buf)>;
  return DoSliceImpl<Poly, Dir>(crc, buf, len, Seq{});
}

// Poly must already be reflected for LsbFirst.
template<std::unsigned_integral auto Poly, Endian Dir, std::size_t Slices = 1>
requires (Slices > 0)
inline auto Compute(std::unsigned_integral auto crc, std::byte b) noexcept
{ return DoSlice<Poly, Dir>(crc, std::to_integer<std::uint8_t>(b)); }

// Poly must already be reflected for LsbFirst.
template<std::unsigned_integral auto Poly, Endian Dir, std::size_t Slices = 1>
requires (Slices == 0)
inline auto Compute(std::unsigned_integral auto crc, std::byte b) noexcept
{ return Update<Poly, Dir>(crc, b); }

// Poly must already be reflected for LsbFirst.
template<std::unsigned_integral auto Poly, Endian Dir, std::size_t Slices = 8>
inline auto Compute(std::unsigned_integral auto crc,
                       std::span<const std::byte> buf) noexcept
  -> decltype(crc);

template<std::unsigned_integral auto Poly, Endian Dir, std::size_t Slices>
requires (Slices==1 || Slices==2 || Slices==4 || Slices==8)
inline auto Compute(std::unsigned_integral auto crc,
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
      crc = DoSlice<Poly, Dir>(crc, p, num);
      p  += num;
      sz -= num;
    }
  }
  auto p2  = reinterpret_cast<const Word*>(p);
  auto sz2 = sz / sizeof(Word);
  crc = DoSlice<Poly, Dir>(crc, p2, sz2);
  sz2 *= sizeof(Word);
  sz -= sz2;
  if (sz > 0) {
    p += sz2;
    crc = DoSlice<Poly, Dir>(crc, p, sz);
  }
  return crc;
} // Compute

template<std::unsigned_integral auto Poly, Endian Dir, std::size_t Slices>
requires (Slices == 0)
inline auto Compute(std::unsigned_integral auto crc,
                       std::span<const std::byte> buf) noexcept
{
  static_assert(sizeof(Poly) <= sizeof(crc));
  for (auto b: buf)
    crc = Update<Poly, Dir>(crc, b);
  return crc;
} // Compute

#undef TJG_IS_LITTLE_ENDIAN

} // detail

template<std::size_t Bits_, uint_t<Bits_>::least Poly_, Endian Dir_,
         std::size_t Slices_ = 8>
requires (Bits_ >= 3 && Bits_ <= 64)
class Crc {
public:
  static constexpr auto   Bits = Bits_;
  static constexpr auto   Poly = Poly_;
  static constexpr Endian Dir  = Dir_;
  static constexpr auto Slices = Slices_;

  using value_type = uint_t<Bits>::least;

protected:
  static constexpr auto CrcBits = 8 * sizeof(value_type);
  static constexpr std::uint8_t Shift = CrcBits - Bits;

private:
  static constexpr value_type FastPoly = (Dir == Endian::MsbFirst)
                                    ? (Poly << Shift)
                                    : (Reflect(Poly) >> Shift);
private:
  const value_type _init;
  const value_type _xor;
  value_type _crc;

  static constexpr value_type Init(value_type init) noexcept {
    if constexpr (Dir == Endian::MsbFirst)
      return static_cast<value_type>(init << Shift);
    else
      return static_cast<value_type>(Reflect(init) >> Shift);
  } // Init

public:
  constexpr void reset() noexcept { _crc = _init; }

  [[nodiscard]] constexpr value_type value() const noexcept {
    if constexpr (Dir == Endian::MsbFirst)
      return (_crc >> Shift) ^ _xor;
    else
      return _crc ^ _xor;
  }

  constexpr Crc(value_type init_, value_type xor_) noexcept
    : _init{Init(init_)} , _xor{xor_} , _crc{_init} { }

  constexpr void update(std::byte b) noexcept
    { _crc = detail::Compute<FastPoly, Dir, Slices>(_crc, b); }

  constexpr void update(std::span<const std::byte> buf) noexcept
    { _crc = detail::Compute<FastPoly, Dir, Slices>(_crc, buf); }

  [[nodiscard]] operator value_type() const { return value(); }

  Crc& operator()(std::span<const std::byte> buf) { update(buf); return *this; }

  Crc& operator()(std::byte b) { update(b); return *this; }
}; // Crc

} // tjg::crc

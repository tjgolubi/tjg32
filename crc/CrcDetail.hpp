#pragma once

#include <array>
#include <span>
#include <concepts>
#include <type_traits>
#include <utility>
#include <bit>
#include <cstdint>
#include <cstddef>

namespace tjg::crc {

enum class Endian { LsbFirst, MsbFirst };

} // tjg::crc

namespace tjg::crc::detail {

// Mask evaluates to either 0 or ~0, depending on the MSB of its
// argument. This is used to & with the polynomial to avoid using a branch.
// The DEBUG implementation runs faster when compiled
// with -O0 or -Og.  For all other optimization levels, the other wins.
constexpr auto MsbMask(std::unsigned_integral auto x) noexcept
  -> decltype(x)
{
  using Uint = decltype(x);
  using Int  = std::make_signed_t<Uint>;
#ifndef DEBUG
  return -(Uint)((Int) x < Int{0});
#else
  static constexpr auto Shift = 8 * sizeof(x) - 1;
  return (Uint)((Int) x >> Shift);
#endif
} // MsbMask

// Mask evaluates to either 0 or ~0, depending on the LSB of its
// argument. This is used to & with the polynomial to avoid using a branch.
constexpr auto LsbMask(std::unsigned_integral auto x) noexcept
  -> decltype(x)
{
  return -(x & 1);
} // LsbMask

// Poly must already be reflected.
template<std::unsigned_integral auto Poly, Endian Dir>
requires (Dir == Endian::MsbFirst)
constexpr auto Update(std::unsigned_integral auto crc, bool in) noexcept
  -> decltype(crc)
{
  using Uint = decltype(crc);
  crc ^= static_cast<Uint>(in) << (8 * sizeof(Uint)-1);
  return (crc << 1) ^ (MsbMask(crc) & Poly);
} // Update MsbFirst

// Poly must already be reflected.
template<std::unsigned_integral auto Poly, Endian Dir>
requires (Dir == Endian::LsbFirst)
constexpr auto Update(std::unsigned_integral auto crc, bool in) noexcept
  -> decltype(crc)
{
  using Uint = decltype(crc);
  crc ^= static_cast<Uint>(in);
  return (crc >> 1) ^ (LsbMask(crc) & Poly);
} // Update LsbFirst

// Poly must already be reflected.
template<std::unsigned_integral auto Poly, Endian Dir>
requires (Dir == Endian::MsbFirst)
constexpr auto Update(std::unsigned_integral auto crc, std::byte in) noexcept
  -> decltype(crc)
{
  using Uint = decltype(crc);
  crc ^= std::to_integer<Uint>(in) << (8 * (sizeof(Uint)-1));
  for (int i = 0; i != 8; ++i)
    crc = (crc << 1) ^ (MsbMask(crc) & Poly);
  return crc;
} // Update MsbFirst

// Poly must already be reflected.
template<std::unsigned_integral auto Poly, Endian Dir>
requires (Dir == Endian::LsbFirst)
constexpr auto Update(std::unsigned_integral auto crc, std::byte in) noexcept
  -> decltype(crc)
{
  using Uint = decltype(crc);
  crc ^= std::to_integer<Uint>(in);
  for (int i = 0; i != 8; ++i)
    crc = (crc >> 1) ^ (LsbMask(crc) & Poly);
  return crc;
} // Update LsbFirst

template<std::unsigned_integral Uint, Uint Poly, Endian Dir, std::size_t Slice>
class Lookup : public std::array<Uint, 256> {
private:
  using Table = std::array<Uint, 256>;

  static consteval Table Generate() noexcept
  requires (Slice == 0 && Dir == Endian::MsbFirst)
  {
    auto table = Table{};
    static constexpr auto Shift = 8 * sizeof(Uint) - 1;
    Uint crc = Uint{1} << Shift;
    table[0] = Uint{0};
    for (unsigned i = 0x01; i != 0x100; i <<= 1) {
      crc = (crc << 1) ^ (MsbMask(crc) & Poly);
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
      crc = (crc >> 1) ^ (LsbMask(crc) & Poly);
      for (unsigned j = 0; j < 256; j += 2 * i)
        table[i+j] = crc ^ table[j];
    }
    return table;
  }; // Generate

  static consteval Table Generate() noexcept
  requires (Slice > 0 && Slice <= 8)
  {
    auto table = Table{};
    auto& Tbl0 = Lookup<Uint, Poly, Dir, 0>::Get();
    auto& Prev = Lookup<Uint, Poly, Dir, Slice-1>::Get();
    static constexpr auto Shift = 8 * sizeof(Uint) - 8;
    for (int i = 0; i != 256; ++i) {
      auto crc = Prev[i];
      if (Dir == Endian::LsbFirst)
        table[i] = (crc >> 8) ^ Tbl0[(std::uint8_t) crc];
      else
        table[i] = (crc << 8) ^ Tbl0[(std::uint8_t) (crc >> Shift)];
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
constexpr auto DoSlice(auto crc, std::uint8_t byte) noexcept {
  using std::uint8_t;
  using Uint = decltype(crc);
  static constexpr const auto& Table = Lookup<Uint, Poly, Dir, 0>::Get();
  if (Dir == Endian::LsbFirst)
    return Rsh<1>(crc) ^ Table[byte ^ (uint8_t) crc];
  else
    return Lsh<1>(crc) ^ Table[byte ^ (uint8_t) Rsh<sizeof(Uint)-1>(crc)];
} // DoSlice

constexpr bool IsLittleEndian() noexcept {
#ifndef TJG_DEBUG_ENDIAN
  return (std::endian::native == std::endian::little);
#else
  return (std::endian::native != std::endian::little);
#endif
} // IsLittleEndian

constexpr auto DebugByteSwap(auto n) noexcept {
#ifdef TJG_DEBUG_ENDIAN
  return std::byteswap(n);
#else
  return n;
#endif
} // DebugByteSwap

template<std::unsigned_integral Uint, Uint Poly, Endian Dir, std::size_t Slice>
constexpr Uint Term(Uint crc, auto word) noexcept {
  using std::uint8_t;
  static constexpr const auto& Table = Lookup<Uint, Poly, Dir, Slice>::Get();
  static constexpr int S = Slice;
  static constexpr int C = sizeof(Uint);
  static constexpr int N = sizeof(word) - 1;
  static constexpr int X = (Dir == Endian::LsbFirst) ? (N-S) : ((C-1) - (N-S));
  static constexpr int W = IsLittleEndian() ? (N-Slice) : Slice;
  return Table[(uint8_t) Rsh<W>(word) ^ (uint8_t) Rsh<X>(crc)];
}

template<std::unsigned_integral auto Poly, Endian Dir, std::size_t... SliceVals>
constexpr auto DoSliceImpl(auto crc, const auto* buf, std::size_t len,
                           std::index_sequence<SliceVals...>) noexcept
{
  using Uint = decltype(crc);
  static constexpr int W = sizeof(*buf);
  while (len--) {
    auto n = DebugByteSwap(*buf++);
    crc = ((Dir == Endian::LsbFirst) ? Rsh<W>(crc) : Lsh<W>(crc))
        ^ (Term<Uint, Poly, Dir, SliceVals>(crc, n) ^ ...);
  }
  return crc;
} // DoSliceImpl

template<std::unsigned_integral auto Poly, Endian Dir>
constexpr auto DoSlice(auto crc, const auto* buf, std::size_t len) noexcept {
  using Seq = std::make_index_sequence<sizeof(*buf)>;
  return DoSliceImpl<Poly, Dir>(crc, buf, len, Seq{});
}

// Poly must already be reflected for LsbFirst.
template<std::unsigned_integral auto Poly, Endian Dir>
constexpr auto Compute(std::unsigned_integral auto crc, bool bit) noexcept
  -> decltype(crc)
{ return Update<Poly, Dir>(crc, bit); }

// Poly must already be reflected for LsbFirst.
template<std::unsigned_integral auto Poly, Endian Dir, std::size_t Slices>
constexpr auto Compute(std::unsigned_integral auto crc, std::byte b) noexcept
  -> decltype(crc);

// Poly must already be reflected for LsbFirst.
template<std::unsigned_integral auto Poly, Endian Dir, std::size_t Slices>
constexpr auto Compute(std::unsigned_integral auto crc,
                       std::span<const std::byte> buf) noexcept
  -> decltype(crc);

template<std::unsigned_integral auto Poly, Endian Dir, std::size_t Slices>
requires (Slices > 0)
constexpr auto Compute(std::unsigned_integral auto crc, std::byte b) noexcept
{ return DoSlice<Poly, Dir>(crc, std::to_integer<std::uint8_t>(b)); }

template<std::unsigned_integral auto Poly, Endian Dir, std::size_t Slices>
requires (Slices == 0)
constexpr auto Compute(std::unsigned_integral auto crc, std::byte b) noexcept
{ return Update<Poly, Dir>(crc, b); }

template<std::unsigned_integral auto Poly, Endian Dir, std::size_t Slices>
requires (Slices == 0)
constexpr auto Compute(std::unsigned_integral auto crc,
                       std::span<const std::byte> buf) noexcept
{
  for (auto b: buf)
    crc = Update<Poly, Dir>(crc, b);
  return crc;
} // Compute

template<std::unsigned_integral auto Poly, Endian Dir, std::size_t Slices>
requires (Slices == 1)
constexpr auto Compute(std::unsigned_integral auto crc,
                        std::span<const std::byte> buf) noexcept
{
  auto p  = reinterpret_cast<const std::uint8_t*>(buf.data());
  return DoSlice<Poly, Dir>(crc, p, buf.size());
} // Compute

template<std::size_t N> struct WordT;
template<> struct WordT<1> { using type = std::uint8_t;  };
template<> struct WordT<2> { using type = std::uint16_t; };
template<> struct WordT<4> { using type = std::uint32_t; };
template<> struct WordT<8> { using type = std::uint64_t; };

template<std::unsigned_integral auto Poly, Endian Dir, std::size_t Slices>
requires (Slices==2 || Slices==4 || Slices==8)
constexpr auto Compute(std::unsigned_integral auto crc,
                       std::span<const std::byte> buf) noexcept
{
  if (buf.empty())
    return crc;
  using Uint = decltype(crc);
  using Word = WordT<Slices>::type;
  auto p  = reinterpret_cast<const std::uint8_t*>(buf.data());
  auto sz = buf.size();
  // Process non-slice-aligned initial bytes.
  auto num = static_cast<std::size_t>(
                                  reinterpret_cast<std::uintptr_t>(p) % Slices);
  if (num != 0) {
    num = Slices - num;
    crc = DoSlice<Poly, Dir>(crc, p, num);
    p  += num;
    sz -= num;
  }
  // Process slice-aligned bytes.
  auto p2  = reinterpret_cast<const Word*>(p);
  auto sz2 = sz / sizeof(Word);
  crc = DoSlice<Poly, Dir>(crc, p2, sz2);
  // Process non-slice-aligned trailing bytes.
  sz2 *= sizeof(Word);
  sz -= sz2;
  if (sz > 0) {
    p += sz2;
    crc = DoSlice<Poly, Dir>(crc, p, sz);
  }
  return crc;
} // Compute

} // tjg::crc::detail

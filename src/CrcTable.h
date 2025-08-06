/// @file
/// @copyright 2025 Terry Golubiewski, all rights reserved.
/// Header-only compile-time sliced CRC engine for C++23
/// @author Terry Golubiewski

#pragma once

#include "CrcUpdate.h"

#include <concepts>
#include <array>
#include <cstddef>

namespace tjg {


template<std::unsigned_integral Uint, Uint Poly, CrcDir Dir, std::size_t Slice>
struct Generator {
  using Table = std::array<Uint, 256>;
  static consteval Table Generate() noexcept;
}; //Generator

template<std::unsigned_integral Uint, Uint Poly, CrcDir Dir, std::size_t Slice>
class CrcTable : public std::array<Uint, 256> {
private:
  using Table = std::array<Uint, 256>;

  static consteval Table Generate() noexcept
  requires (Slice == 0 && Dir == CrcDir::MsbFirst)
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
  requires (Slice == 0 && Dir == CrcDir::LsbFirst)
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
    auto& Tbl0=CrcTable<Uint, Poly, Dir, 0>::Get();
    auto& Prev=CrcTable<Uint, Poly, Dir, Slice-1>::Get();
    static constexpr auto Shift = 8 * sizeof(Uint) - 8;
    for (int i = 0; i != 256; ++i) {
      auto crc = Prev[i];
      if (Dir == CrcDir::LsbFirst)
        table[i] = (crc >> 8) ^ Tbl0[(std::uint8_t) crc];
      else
        table[i] = (crc << 8) ^ Tbl0[crc >> Shift];
    }
    return table;
  }; // Generate

  constexpr CrcTable() : Table{Generate()} { }

public:
  static constexpr const CrcTable& Get() noexcept {
    static constexpr auto TheTable = CrcTable{};
    return TheTable;
  }
}; // CrcTable

} // tjg

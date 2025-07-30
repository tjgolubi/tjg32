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

// Forward declaration for primary template
template<std::unsigned_integral Uint, Uint Poly, CrcDir Dir, std::size_t Slice>
class CrcTable : public std::array<Uint, 256> {
private:
  consteval std::array<Uint, 256> Generate() noexcept {
    std::array<Uint, 256> table{};
    if constexpr (Slice == 0) {
      for (std::size_t i = 0; i < 256; ++i) {
        table[i] =
                CrcUpdate<Uint, Poly, Dir>(Uint{0}, static_cast<std::byte>(i));
      }
    }
    else {
      for (int i = 0; i < 256; ++i) {
        auto crc = CrcTable<Uint, Poly, Dir, Slice-1>::Get()[i];
        table[i] = CrcUpdate<Uint, Poly, Dir>(crc, std::byte{0});
      }
    }
    return table;
  } // Generate

  constexpr CrcTable() : std::array<Uint, 256>{Generate()} {}

public:
  static constexpr const CrcTable& Get() noexcept {
    static constexpr auto Table = CrcTable{};
    return Table;
  }
}; // CrcTable

} // tjg

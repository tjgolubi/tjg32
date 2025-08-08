/// @file
/// @copyright 2025 Terry Golubiewski, all rights reserved.
/// @author Terry Golubiewski
/// Provides uint_t<int Bits>.

#pragma once

#include <cstdint>
#include <cstddef>

namespace tjg {

template<int N>
struct uint_t_helper;

template<>
struct uint_t_helper<0> {
  using least = std::uint8_t;
}; // uint_t_helper

template<>
struct uint_t_helper<1> {
  using least = std::uint16_t;
}; // uint_t_helper

template<>
struct uint_t_helper<2> {
  using least = std::uint32_t;
}; // uint_t_helper

template<>
struct uint_t_helper<3> {
  using least = std::uint64_t;
}; // uint_t_helper

template<std::size_t Bits>
requires (Bits > 0 && Bits <= 64)
struct uint_t: public uint_t_helper<(Bits > 8) + (Bits > 16) + (Bits > 32)> {

}; // uint_t

} // tjg

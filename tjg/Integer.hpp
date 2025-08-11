/// @file
/// @copyright 2025 Terry Golubiewski, all rights reserved.
/// @author Terry Golubiewski
/// Provides int_t<Bits> and uint_t<Bits>.

#pragma once

#include <cstdint>
#include <cstddef>

namespace tjg {

/// @internal
namespace detail {

constexpr int Index(std::size_t Bits)
{ return (Bits > 8) + (Bits > 16) + (Bits > 32); }

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

} // detail

template<std::size_t Bits>
requires (Bits > 0 && Bits <= 64)
struct uint_t: detail::uint_t_helper<detail::Index(Bits)> { };

/// @internal
namespace detail {

template<int N>
struct int_t_helper;

template<>
struct int_t_helper<0> {
  using least = std::int8_t;
}; // int_t_helper

template<>
struct int_t_helper<1> {
  using least = std::int16_t;
}; // int_t_helper

template<>
struct int_t_helper<2> {
  using least = std::int32_t;
}; // int_t_helper

template<>
struct int_t_helper<3> {
  using least = std::int64_t;
}; // int_t_helper

} // detail

template<std::size_t Bits>
requires (Bits > 0 && Bits <= 64)
struct int_t: detail::int_t_helper<detail::Index(Bits)> { };

} // tjg

#include "tjg/Integer.hpp"

#include <type_traits>

// Is IntT<Bits> a valid type?
template<template<std::size_t> class IntT, std::size_t Bits>
concept IntTAvailable = requires { typename IntT<Bits>; };

// Negative tests (works even if IntT is constrained: no member access)
static_assert(!IntTAvailable<tjg::uint_t,  0>);
static_assert(!IntTAvailable<tjg::uint_t, 65>);
static_assert( IntTAvailable<tjg::uint_t,  1>);
static_assert( IntTAvailable<tjg::uint_t, 64>);
static_assert(!IntTAvailable<tjg::int_t,   0>);
static_assert(!IntTAvailable<tjg::int_t,  65>);
static_assert( IntTAvailable<tjg::int_t,   1>);
static_assert( IntTAvailable<tjg::int_t,  64>);

#define UINT_CHECK(B, T) static_assert(std::is_same_v<tjg::uint_t<B>::least, T>)

UINT_CHECK( 1, std::uint8_t);
UINT_CHECK( 2, std::uint8_t);
UINT_CHECK( 3, std::uint8_t);
UINT_CHECK( 4, std::uint8_t);
UINT_CHECK( 5, std::uint8_t);
UINT_CHECK( 6, std::uint8_t);
UINT_CHECK( 7, std::uint8_t);
UINT_CHECK( 8, std::uint8_t);
UINT_CHECK( 9, std::uint16_t);
UINT_CHECK(15, std::uint16_t);
UINT_CHECK(16, std::uint16_t);
UINT_CHECK(17, std::uint32_t);
UINT_CHECK(31, std::uint32_t);
UINT_CHECK(32, std::uint32_t);
UINT_CHECK(33, std::uint64_t);
UINT_CHECK(63, std::uint64_t);
UINT_CHECK(64, std::uint64_t);

#define INT_CHECK(B, T) static_assert(std::is_same_v<tjg::int_t<B>::least, T>)

INT_CHECK( 1, std::int8_t);
INT_CHECK( 2, std::int8_t);
INT_CHECK( 3, std::int8_t);
INT_CHECK( 4, std::int8_t);
INT_CHECK( 5, std::int8_t);
INT_CHECK( 6, std::int8_t);
INT_CHECK( 7, std::int8_t);
INT_CHECK( 8, std::int8_t);
INT_CHECK( 9, std::int16_t);
INT_CHECK(15, std::int16_t);
INT_CHECK(16, std::int16_t);
INT_CHECK(17, std::int32_t);
INT_CHECK(31, std::int32_t);
INT_CHECK(32, std::int32_t);
INT_CHECK(33, std::int64_t);
INT_CHECK(63, std::int64_t);
INT_CHECK(64, std::int64_t);

int main() {
  return 0;
} // main

/// @file
/// @copyright 2025 Terry Golubiewski, all rights reserved.
/// @author Terry Golubiewski
///
/// Google Test port of the CRC traits test runner.
///
/// Uses a typed test suite instantiated from the boost::mp11::mp_list of known
/// CRC traits in crc/CrcKnown.hpp.  For each trait T, we verify:
///
///   1) The "check" vector "123456789" yields the expected T::Check value.
///   2) Slicing-by-0 and the default slicing configuration compute identical
///      results over various spans of a constexpr test buffer.
///
/// The type list is provided by tjg::crc::test_detail::KnownCrcs (an
/// mp11::mp_list<...>).  We transform it to a ::testing::Types<...> with
/// mp11::mp_apply so we do not need to spell out all types.

#include "crc/CrcKnown.hpp"

#include <gtest/gtest.h>

#include <boost/mp11/list.hpp>
#include <boost/mp11/algorithm.hpp>

#include <array>
#include <span>
#include <iomanip>
#include <ostream>
#include <sstream>
#include <concepts>
#include <type_traits>
#include <cstddef>

// ------------------------------------------------------------------
// Utilities kept from the original test for readable diagnostics
// ------------------------------------------------------------------

template<std::unsigned_integral U>
struct CoutType: public std::conditional<(sizeof(U) == 1), unsigned, U>
{ };

template<std::unsigned_integral U>
auto Value(U x) -> typename CoutType<U>::type
  { return static_cast<typename CoutType<U>::type>(x); }

alignas(64) constexpr auto TestBuf = std::array<std::byte, 9>{
  std::byte{'1'}, std::byte{'2'}, std::byte{'3'},
  std::byte{'4'}, std::byte{'5'}, std::byte{'6'},
  std::byte{'7'}, std::byte{'8'}, std::byte{'9'}
}; // TestBuf

template<std::size_t N>
constexpr auto GenerateData() -> std::array<std::byte, N> {
  auto result = std::array<std::byte, N>{};
  for (std::size_t i = 0; i != N; ++i)
    result[i] = std::byte((i + 1) & 0xff);
  return result;
} // GenerateData

alignas(64) constinit auto TestData = GenerateData<256>();

template<class CrcTraits, std::size_t Slices>
static void AppendFailure(std::ostream& os,
                          const tjg::crc::Known<CrcTraits, Slices>& crc,
                          typename CrcTraits::value_type expected)
{
  using Crc = tjg::crc::Known<CrcTraits>;
  int width = 2 * int(sizeof(typename Crc::value_type));
  os << "\nBits         =   " << std::dec << Crc::Bits << std::hex
     << "\nPoly         = 0x" << std::setw(width) << Value(Crc::Poly)
     << "\nDir          =   "
     << ((Crc::Dir == tjg::crc::Endian::LsbFirst) ? "LSB" : "MSB")
     << "\nSlices       =   " << Slices
     << "\nCheck        = 0x" << std::setw(width) << Value(crc.value())
     << "\nCrc          = 0x" << std::setw(width) << Value(expected);
} // AppendFailure

// ------------------------------------------------------------------
// Google Test typed test suite
// ------------------------------------------------------------------

template<class CrcTraits>
class CrcTypedTest: public ::testing::Test { };

using CrcMpList = tjg::crc::test_detail::KnownCrcs;

// Transform mp_list<T...> -> ::testing::Types<T...>
using CrcTypes = boost::mp11::mp_apply<::testing::Types, CrcMpList>;

TYPED_TEST_SUITE(CrcTypedTest, CrcTypes);

// --------------------------------------------------------------
// Test 1: The canonical "123456789" check vector
// --------------------------------------------------------------
TYPED_TEST(CrcTypedTest, CheckVector) {
  using Crc = tjg::crc::Known<TypeParam, 8>;
  Crc crc;
  crc.update(TestBuf);
  auto got = crc.value();
  auto exp = Crc::Check;
  EXPECT_EQ(got, exp) << [&]() {
      std::ostringstream os;
      AppendFailure(os, crc, exp);
      return os.str();
    }();
}

// --------------------------------------------------------------
// Test 2: Slicing-by-0 vs slice-by-8
// --------------------------------------------------------------
namespace detail {

template<class CrcTraits,
         std::size_t N = TestData.size(),
         std::size_t Offset = 0>
requires (N > 0 && N + Offset <= TestData.size())
void VaryingSizeSlice0vs8() {
  using Crc0 = tjg::crc::Known<CrcTraits, 0>;
  using Crc  = tjg::crc::Known<CrcTraits, 8>;
  auto data = std::span{TestData.data() + Offset, N};
  Crc0 c0;
  c0.update(data);
  Crc c;
  c.update(data);
  if (c != c0) {
    std::ostringstream os;
    AppendFailure(os, c, c0.value());
    ADD_FAILURE() << "Mismatch for span N=" << N
                  << " Offset=" << Offset << os.str();
  }
} // ExpectSameForSpan

} // detail

TYPED_TEST(CrcTypedTest, SlicingParityOnSpans) {
  // Mirror the exact calls present in the original test:
  //  - default N (== TestData.size()) and Offset 0
  detail::VaryingSizeSlice0vs8<TypeParam>();
  detail::VaryingSizeSlice0vs8<TypeParam, 127, 0>();
  detail::VaryingSizeSlice0vs8<TypeParam, 128, 0>();
  detail::VaryingSizeSlice0vs8<TypeParam, 129, 0>();
  detail::VaryingSizeSlice0vs8<TypeParam, 129, 5>();
}


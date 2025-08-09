// meta.cpp

#include "tjg/meta.hpp"

#include <type_traits>
#include <array>
#include <cstdint>

#include <iostream>

using meta::TypeList;

namespace test_detail {

// Expect equal typelists
template<typename A, typename B>
constexpr bool Same = std::is_same_v<A, B>;

// Make some lists
using L0 = TypeList<>;
using L1 = TypeList<int>;
using L3 = TypeList<int, char, long>;

} // test_detail

// ----- NthType -----
static_assert(std::is_same_v<meta::NthTypeT<0, test_detail::L3>, int>);
static_assert(std::is_same_v<meta::NthTypeT<1, test_detail::L3>, char>);
static_assert(std::is_same_v<meta::NthTypeT<2, test_detail::L3>, long>);

// Uncomment to verify out-of-bounds is ill-formed (should fail to compile).
// using OB = meta::NthTypeT<3, test_detail::L3>;

// ----- Prepend -----
using Pre1 = typename meta::Prepend<test_detail::L0, bool>::type;
static_assert(test_detail::Same<Pre1, TypeList<bool>>);

using Pre2 = typename meta::Prepend<test_detail::L3, bool>::type;
static_assert(test_detail::Same<Pre2, TypeList<bool, int, char, long>>);

// ----- Append -----
using App1 = typename meta::Append<test_detail::L0, bool>::type;
static_assert(test_detail::Same<App1, TypeList<bool>>);

using App2 = typename meta::Append<test_detail::L3, bool>::type;
static_assert(test_detail::Same<App2, TypeList<int, char, long, bool>>);

// ----- Concat -----
using Cat1 = typename meta::Concat<test_detail::L0, test_detail::L1>::type;
static_assert(test_detail::Same<Cat1, TypeList<int>>);

using Cat2 = typename meta::Concat<test_detail::L1, test_detail::L3>::type;
static_assert(test_detail::Same<Cat2, TypeList<int, int, char, long>>);

// ----- Filter -----
// Use std::is_integral as predicate; Filter expects P<T>::value.
using F0 = meta::FilterT<std::is_integral, test_detail::L0>;
static_assert(test_detail::Same<F0, TypeList<>>);

using F1 = meta::FilterT<std::is_integral, TypeList<float, int, char, double>>;
static_assert(test_detail::Same<F1, TypeList<int, char>>);

// If meta::Filter short-circuits correctly, complex lists should pass.
using F2 = meta::FilterT<std::is_unsigned,
                         TypeList<std::int8_t,
                                  std::uint8_t,
                                  std::uint16_t,
                                  float,
                                  std::uint32_t,
                                  double>>;
static_assert(test_detail::Same<F2,
                                TypeList<std::uint8_t,
                                         std::uint16_t,
                                         std::uint32_t>>);

// ----- ForEachType -----

// Verifies that ForEachType iterates in-order over the typelist and
// invokes either `fn.template operator()<T>()` or
// `fn(TypeTag<T>{})`. Adjust the typelist if you prefer other types.

namespace test_detail {

template<class T> struct TypeId;
template<> struct TypeId<int>        { static constexpr int v = 0; };
template<> struct TypeId<char>       { static constexpr int v = 1; };
template<> struct TypeId<long>       { static constexpr int v = 2; };
template<> struct TypeId<bool>       { static constexpr int v = 3; };

using Lf = TypeList<int, char, long, bool>;

struct Recorder {
  int* out;
  int* idx;

  // Style A: meta calls fn.template operator()<T>()
  template<class T>
  constexpr void operator()() const noexcept {
    out[(*idx)++] = TypeId<T>::v;
  }

  // Style B: meta calls fn(TypeTag<T>{})
  template<class T>
  constexpr void operator()(meta::TypeTag<T>) const noexcept {
    out[(*idx)++] = TypeId<T>::v;
  }
}; // Recorder

} // test_detail

constexpr bool TestForEachType() noexcept {
  std::array<int, 4> got{ -1, -1, -1, -1 };
  std::array<int, 4> exp{ 0, 1, 2, 3 };
  int idx = 0;

  test_detail::Recorder rec{ got.data(), &idx };
  meta::ForEachType<test_detail::Lf>(rec);

  if (idx != 4)
    return false;

  return (got == exp);;
} // TestForEachType

static_assert(TestForEachType());

int main() {
  if (!TestForEachType()) {
    std::cout << "TestForEachType failed" << std::endl;
    return 1;
  }
  return 0;
} // main

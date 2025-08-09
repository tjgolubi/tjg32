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

// ----- ForEachType: empty list makes no calls (constexpr) -----
namespace td_empty {

struct Count {
  static constexpr int start = 123;
  mutable int n = start;

  template<class T>
  constexpr void operator()() const { ++n; }

  template<class T>
  constexpr void operator()(meta::TypeTag<T>) const { ++n; }
};

constexpr bool Run() {
  Count c{};
  meta::ForEachType<meta::TypeList<>>(c);
  return c.n == Count::start;
}

static_assert(Run());

} // namespace td_empty

// ----- ForEachType: single-element, both invocation styles -----
namespace td_single {

struct OpTpl {
  template<class T>
  constexpr void operator()() const noexcept {}
};
struct OpTag {
  template<class T>
  constexpr void operator()(meta::TypeTag<T>) const noexcept {}
};

using L1 = meta::TypeList<int>;

static_assert(noexcept(meta::ForEachType<L1>(OpTpl{})));
static_assert(noexcept(meta::ForEachType<L1>(OpTag{})));

} // namespace td_single

// ----- ForEachType: mixed per-T dispatch; noexcept must reflect mix -----
namespace td_mixed {

using L = meta::TypeList<int, float, long>;

struct Mixed {
  // Integral T -> template call, noexcept
  template<class T>
  constexpr void operator()() const noexcept
    requires std::is_integral_v<T> {}

  // Non-integral T -> tag call, not noexcept
  template<class T>
  constexpr void operator()(meta::TypeTag<T>) const
    requires (!std::is_integral_v<T>) {}
};

static_assert(!noexcept(meta::ForEachType<L>(Mixed{})));

// Also check the all-integral case becomes noexcept.
using Lint = meta::TypeList<int, long, char>;
static_assert(noexcept(meta::ForEachType<Lint>(Mixed{})));

} // namespace td_mixed

// ----- ForEachType: order sanity (compile-time) -----
namespace td_order {

template<class T> struct Id;
template<> struct Id<int>   { static constexpr int v = 0; };
template<> struct Id<char>  { static constexpr int v = 1; };
template<> struct Id<long>  { static constexpr int v = 2; };
template<> struct Id<float> { static constexpr int v = 3; };

using L = meta::TypeList<int, char, long, float>;

struct Rec {
  int* out; int* idx;

  template<class T>
  constexpr void operator()() const { out[(*idx)++] = Id<T>::v; }

  template<class T>
  constexpr void operator()(meta::TypeTag<T>) const
  { out[(*idx)++] = Id<T>::v; }
};

constexpr bool Run() {
  int buf[4] = { -1, -1, -1, -1 };
  int i = 0;
  Rec r{ buf, &i };
  meta::ForEachType<L>(r);
  return i == 4 && buf[0] == 0 && buf[1] == 1
         && buf[2] == 2 && buf[3] == 3;
}

static_assert(Run());

} // namespace td_order

// ----- Concat: quick regression (left-to-right) -----
namespace td_concat {
using A = meta::TypeList<int>;
using B = meta::TypeList<char, long>;
using C = meta::ConcatT<A, B>;
static_assert(std::is_same_v<C, meta::TypeList<int, char, long>>);
} // namespace td_concat

// ----- Filter: stability (preserves order) -----
namespace td_filter {
using In  = meta::TypeList<float, int, char, double, long>;
using Out = meta::FilterT<std::is_integral, In>;
static_assert(std::is_same_v<Out, meta::TypeList<int, char, long>>);
} // namespace td_filter

// ----- Unique: stability and idempotence -----
namespace td_unique {
// duplicates interleaved; keep firsts, preserve order
using D = meta::TypeList<int, int, char, int, char, long, long>;
using U = meta::UniqueT<D>;
static_assert(std::is_same_v<U, meta::TypeList<int, char, long>>);

// already unique -> unchanged
using A = meta::TypeList<int, char, long>;
static_assert(std::is_same_v<meta::UniqueT<A>, A>);

// empty and single
static_assert(std::is_same_v<meta::UniqueT<meta::TypeList<>>,
                             meta::TypeList<>>);
static_assert(std::is_same_v<meta::UniqueT<meta::TypeList<int>>,
                             meta::TypeList<int>>);

// Contains helper sanity
static_assert( meta::ContainsV<meta::TypeList<int, char>, int>);
static_assert(!meta::ContainsV<meta::TypeList<int, char>, float>);
} // namespace td_unique

// Size, Front and Back
static_assert(meta::SizeV<meta::TypeList<>> == 0);
using Labc = meta::TypeList<int,char,long>;
static_assert(meta::SizeV<Labc> == 3);
static_assert(std::is_same_v<meta::FrontT<Labc>, int>);
static_assert(std::is_same_v<meta::BackT<Labc>,  long>);

// Contains
static_assert( meta::ContainsV<meta::TypeList<int,char>, int>);
static_assert(!meta::ContainsV<meta::TypeList<int,char>, float>);

// If you have IndexOfC (or IndexOfV) with 0-based index:
static_assert(meta::IndexOfC<meta::TypeList<int,char,long>, char>::value == 1);

// If you provide a not-found form (IndexOfOrN):
static_assert(meta::IndexOfV<meta::TypeList<int,char>, float> == -1);

// PopFront
using PFr = typename meta::Prepend<meta::TypeList<char,long>, int>::type;
static_assert(std::is_same_v<PFr, meta::TypeList<int,char,long>>);

using PBa = typename meta::Append<meta::TypeList<int,char>, long>::type;
static_assert(std::is_same_v<PBa, meta::TypeList<int,char,long>>);

using PF  = meta::PopFrontT<meta::TypeList<int,char,long>>;
static_assert(std::is_same_v<PF, meta::TypeList<char,long>>);

// Transform
template<class T> struct AddConst { using type = const T; };
using Tin  = meta::TypeList<int,char,long>;
using Tout = meta::TransformT<AddConst, Tin>;
static_assert(std::is_same_v<Tout,
                             meta::TypeList<const int,const char,const long>>);

// Transform (alias template also works)
template<class T> using AddConstA = std::add_const_t<T>;
using Tout2 = meta::TransformT<AddConstA, Tin>;
static_assert(std::is_same_v<Tout2, Tout>);


// ----- Partition: integrals vs non-integrals (stable) -----
namespace td_partition {
using L = meta::TypeList<float, int, char, double, long>;
using P = meta::Partition<std::is_integral, L>;

static_assert(std::is_same_v<typename P::First,
                             meta::TypeList<int, char, long>>);
static_assert(std::is_same_v<typename P::Second,
                             meta::TypeList<float, double>>);
} // namespace td_partition

#if 0
using Lmix = meta::TypeList<float,int,char,double,long>;
static_assert(meta::CountIfV<std::is_integral, Lmix> == 3);
static_assert( meta::AllOfV<std::is_integral, meta::TypeList<int,long>>);
static_assert(!meta::AllOfV<std::is_integral, Lmix>);
static_assert( meta::AnyOfV<std::is_floating_point, Lmix>);
static_assert(!meta::NoneOfV<std::is_integral, Lmix>);

// ForEachTypeIf

struct CountInts {
  int n = 0;
  template<class T> constexpr void operator()() noexcept
    requires std::is_integral_v<T> { ++n; }
  template<class T> constexpr void operator()(meta::TypeTag<T>) noexcept
    requires std::is_integral_v<T> { ++n; }
};
constexpr bool TestFEI() {
  CountInts c{};
  meta::ForEachTypeIf<meta::TypeList<int,float,long,char>>(c,
                                                           std::is_integral{});
  return c.n == 3;
}
static_assert(TestFEI());
#endif

int main() {
  if (!TestForEachType()) {
    std::cout << "TestForEachType failed" << std::endl;
    return 1;
  }
  return 0;
} // main

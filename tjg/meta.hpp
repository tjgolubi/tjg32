/// @file
/// @copyright 2025 Terry Golubiewski, all rights reserved.
/// @author Terry Golubiewski
/// Meta-programming Type Lists.

#pragma once

#include <type_traits>
#include <tuple>
#include <utility>

namespace meta {

template<typename... Types>
struct TypeList {};

using EmptyList = TypeList<>;

/// Check if a typelist is empty
template<typename List>
constexpr bool IsEmptyV = false;

template<>
constexpr bool IsEmptyV<TypeList<>> = true;

/// Get the number of types in the list
template<typename List>
constexpr std::size_t SizeV = 0;

template<typename... Types>
constexpr std::size_t SizeV<TypeList<Types...>> = sizeof...(Types);

/// Get the first type in a typelist
template<typename List>
struct Front;

template<typename Head, typename... Tail>
struct Front<TypeList<Head, Tail...>> {
  using type = Head;
};

template<typename List>
using FrontT = typename Front<List>::type;

/// Remove the first type from a typelist
template<typename List>
struct PopFront;

template<typename Head, typename... Tail>
struct PopFront<TypeList<Head, Tail...>> {
  using type = TypeList<Tail...>;
};

template<typename List>
using PopFrontT = typename PopFront<List>::type;

// --- BackT ---

template<class List> struct Back;

template<class T>
struct Back<TypeList<T>> { using type = T; };

template<class T, class... Ts>
struct Back<TypeList<T, Ts...>> : Back<TypeList<Ts...>> { };

template<class List>
using BackT = typename Back<List>::type;

/// Prepend a type before the start of a typelist
template<typename List, typename T>
struct Prepend;

template<typename... Ts, typename T>
struct Prepend<TypeList<Ts...>, T> { using type = TypeList<T, Ts...>; };

template<typename List, typename NewType>
using PrependT = typename Prepend<List, NewType>::type;

/// Append a type to the end of a typelist
template<typename List, typename NewType>
struct Append;

template<typename... Types, typename NewType>
struct Append<TypeList<Types...>, NewType> {
  using type = TypeList<Types..., NewType>;
};

template<typename List, typename NewType>
using AppendT = typename Append<List, NewType>::type;

/// Append a typelist to the end of a typelist
template<typename List1, typename List2>
struct Concat;

template<typename... Ts, typename... Us>
struct Concat<TypeList<Ts...>, TypeList<Us...>> {
  using type = TypeList<Ts..., Us...>;
};

template<typename List1, typename List2>
using ConcatT = typename Concat<List1, List2>::type;

/// Get the type at index I (int). Fails to compile if out of bounds.
template<int I, typename List>
struct NthType;

template<int I, typename... Types>
  requires (I >= 0 && I < static_cast<int>(sizeof...(Types)))
struct NthType<I, TypeList<Types...>> {
  using type = std::tuple_element_t<I, std::tuple<Types...>>;
};

template<int I, typename List>
using NthTypeT = typename NthType<I, List>::type;

/// Try to get the type at index I; returns void if out of bounds
template<int I, typename List>
struct TryNthType {
  using type = void;
};

template<int I, typename... Types>
  requires (I >= 0 && I < static_cast<int>(sizeof...(Types)))
struct TryNthType<I, TypeList<Types...>> {
  using type = std::tuple_element_t<I, std::tuple<Types...>>;
};

template<int I, typename List>
using TryNthTypeT = typename TryNthType<I, List>::type;

/// Get the index of a type in the typelist, or -1 if not found
template<typename List, typename T>
struct IndexOf;

template<typename T>
struct IndexOf<TypeList<>, T> : std::integral_constant<int, -1> {};

template<typename Head, typename... Tail, typename T>
struct IndexOf<TypeList<Head, Tail...>, T> {
 private:
  static constexpr int next = IndexOf<TypeList<Tail...>, T>::value;

 public:
  static constexpr int value = std::is_same_v<Head, T> ? 0 :
                               (next == -1 ? -1 : 1 + next);
};

template<typename List, typename T>
constexpr int IndexOfV = IndexOf<List, T>::value;

template<class List, class T>
using IndexOfC = IndexOf<List, T>; // 'C' to indicate constant type

/// Apply a metafunction F<T> to each type in the list

// --- TransformT ---
// Works with either:  (a) template<class> struct F { using type = ...; }
// or                  (b) template<class> using F = ...;

namespace detail {

template<template<class> class F, class T>
struct Invoke {
  // prefer F<T>::type if present
  template<class U>
  static auto test(int) -> std::type_identity<typename F<U>::type>;
  // else fall back to F<U> (alias template or plain type)
  template<class U>
  static auto test(...) -> std::type_identity<F<U>>;

  using type = typename decltype(test<T>(0))::type;
};

} // detail

template<template<class> class F, class List> struct Transform;

template<template<class> class F, class... Ts>
struct Transform<F, TypeList<Ts...>> {
  using type = TypeList<typename detail::Invoke<F, Ts>::type...>;
};

template<template<class> class F, class List>
using TransformT = typename Transform<F, List>::type;

// ----- Contains -----

template<class List, class T>
struct Contains;

template<class T>
struct Contains<TypeList<>, T> : std::false_type {};

template<class Head, class... Tail, class T>
struct Contains<TypeList<Head, Tail...>, T>
  : std::conditional_t<std::is_same_v<Head, T>,
                        std::true_type,
                        Contains<TypeList<Tail...>, T>> {};

template<class List, class T>
inline constexpr bool ContainsV = Contains<List, T>::value;

// ----- Unique (stable: keeps first occurrences, preserves order) -----

template<class List>
struct Unique;

template<>
struct Unique<TypeList<>> { using type = TypeList<>; };

template<class T, class... Ts>
struct Unique<TypeList<T, Ts...>> {
private:
  using TailU = typename Unique<TypeList<Ts...>>::type;
public:
  using type = std::conditional_t<ContainsV<TailU, T>,
                                  TailU,
                                  ConcatT<TypeList<T>, TailU>>;
};

template<class List>
using UniqueT = typename Unique<List>::type;

// ----- CountIf / AnyOf / AllOf / NoneOf -----

template<template<class> class P, class List>
struct CountIf;

template<template<class> class P, class... Ts>
struct CountIf<P, TypeList<Ts...>>
  : std::integral_constant<std::size_t,
      (std::size_t{0} + ... + (P<Ts>::value ? 1u : 0u))> {};

template<template<class> class P, class List>
constexpr std::size_t CountIfV = CountIf<P, List>::value;

template<template<class> class P, class List>
struct AnyOf;

template<template<class> class P, class... Ts>
struct AnyOf<P, TypeList<Ts...>>
  : std::bool_constant<(false || ... || bool(P<Ts>::value))> {};

template<template<class> class P, class List>
constexpr bool AnyOfV = AnyOf<P, List>::value;

template<template<class> class P, class List>
struct AllOf;

template<template<class> class P, class... Ts>
struct AllOf<P, TypeList<Ts...>>
  : std::bool_constant<(true && ... && bool(P<Ts>::value))> {};

template<template<class> class P, class List>
constexpr bool AllOfV = AllOf<P, List>::value;

template<template<class> class P, class List>
constexpr bool NoneOfV = !AnyOfV<P, List>;

/// Filter a typelist using a predicate P<T>::value
template<template<typename> typename P, typename List>
struct Filter;

template<template<typename> typename P>
struct Filter<P, TypeList<>> {
  using type = TypeList<>;
};

template<template<typename> typename P, typename Head, typename... Tail>
struct Filter<P, TypeList<Head, Tail...>> {
private:
  using TailResult = typename Filter<P, TypeList<Tail...>>::type;
public:
  using type = std::conditional_t<P<Head>::value,
                                  typename Prepend<TailResult, Head>::type,
                                  TailResult>;
};

template<template<typename> typename P, typename List>
using FilterT = typename Filter<P, List>::type;

// Partition<P, List>::First / ::Second
template<template<class> class P, class List>
struct Partition;

template<template<class> class P>
struct Partition<P, TypeList<>> {
  using First = TypeList<>;
  using Second = TypeList<>;
};

template<template<class> class P, class T, class... Ts>
struct Partition<P, TypeList<T, Ts...>> {
private:
  using Rest = Partition<P, TypeList<Ts...>>;
public:
  using First =
    std::conditional_t<P<T>::value,
                       ConcatT<TypeList<T>, typename Rest::First>,
                       typename Rest::First>;
  using Second =
    std::conditional_t<P<T>::value,
                       typename Rest::Second,
                       ConcatT<TypeList<T>, typename Rest::Second>>;
}; // Partition

template<class T> struct TypeTag {};

namespace detail {

// Per-T: detect which invocation exists and use its noexcept
template<class T, class F>
consteval bool NoexceptFor() {
  using FR = std::remove_reference_t<F>;
  if constexpr (requires(FR& g) { g.template operator()<T>(); }) {
    return noexcept(std::declval<FR&>().template operator()<T>());
  } else if constexpr (requires(FR& g) { g(TypeTag<T>{}); }) {
    return noexcept(std::declval<FR&>()(TypeTag<T>{}));
  } else {
    return false; // CallOne will static_assert anyway
  }
}

template<class T, class F>
constexpr void CallOne(F&& f) {
  if constexpr (requires(F& g) { g.template operator()<T>(); }) {
    f.template operator()<T>();
  } else if constexpr (requires(F& g) { g(TypeTag<T>{}); }) {
    f(TypeTag<T>{});
  } else {
    static_assert(sizeof(T) == 0,
      "ForEachType: need operator()<T>() or operator()(TypeTag<T>)");
  }
}

template<class F, class... Ts>
constexpr void ForEachTypes(F&& f, TypeList<Ts...>) {
  (CallOne<Ts>(f), ...);
}

} // detail

// Public API: noexcept iff every per-T invocation is noexcept
template<class List, class F>
constexpr void ForEachType(F&& f) noexcept(
  []<class... Ts>(TypeList<Ts...>*) {
    return (detail::NoexceptFor<Ts, F>() && ...);
  }(static_cast<List*>(nullptr))
) {
  detail::ForEachTypes(std::forward<F>(f), List{});
}

} // meta

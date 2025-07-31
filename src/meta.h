/// @file
/// @copyright 2025 Terry Golubiewski, all rights reserved.
/// @author Terry Golubiewski

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
constexpr std::size_t LengthV = 0;

template<typename... Types>
constexpr std::size_t LengthV<TypeList<Types...>> = sizeof...(Types);

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

/// Append a type to the end of a typelist
template<typename List, typename NewType>
struct Append;

template<typename... Types, typename NewType>
struct Append<TypeList<Types...>, NewType> {
  using type = TypeList<Types..., NewType>;
};

template<typename List, typename NewType>
using AppendT = typename Append<List, NewType>::type;

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

/// Check whether a type T exists in the list
template<typename List, typename T>
constexpr bool ContainsV = false;

template<typename Head, typename... Tail, typename T>
constexpr bool ContainsV<TypeList<Head, Tail...>, T> =
  std::is_same_v<Head, T> || ContainsV<TypeList<Tail...>, T>;

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

/// Apply a metafunction F<T> to each type in the list
template<template<typename> typename F, typename List>
struct Transform;

template<template<typename> typename F, typename... Types>
struct Transform<F, TypeList<Types...>> {
  using type = TypeList<F<Types>...>;
};

template<template<typename> typename F, typename List>
using TransformT = typename Transform<F, List>::type;

/// Visit each type in a typelist using a templated callable
template<typename List, typename Fn>
constexpr void ForEachType(Fn&& fn);

template<typename... Types, typename Fn>
constexpr void ForEachTypeImpl(TypeList<Types...>, Fn&& fn) {
  (fn.template operator()<Types>(), ...);
}

template<typename List, typename Fn>
constexpr void ForEachType(Fn&& fn) {
  ForEachTypeImpl(List{}, std::forward<Fn>(fn));
}

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
  using type = std::conditional_t<
    P<Head>::value,
    typename Append<TailResult, Head>::type,
    TailResult>;
};

template<template<typename> typename P, typename List>
using FilterT = typename Filter<P, List>::type;

} // meta

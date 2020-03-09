#ifndef OBSERVABLES_VECTOR_HPP
#define OBSERVABLES_VECTOR_HPP

#include "arithmetic.hpp"
#include "expression.hpp"

#include <tuple>
#include <type_traits>

namespace mdx {
namespace Expression {
template <class... Expr> struct Vector;
template <class Expr> struct Vector<Expr> { using X = Expr; };
template <class Expr1, class Expr2> struct Vector<Expr1, Expr2> {
  using X = Expr1;
  using Y = Expr2;
};
template <class Expr1, class Expr2, class Expr3>
struct Vector<Expr1, Expr2, Expr3> {
  using X = Expr1;
  using Y = Expr2;
  using Z = Expr3;
};

template <class T> constexpr bool is_vector = false;
template <class... Expr> constexpr bool is_vector<Vector<Expr...>> = true;

namespace detail {
template <size_t, class> struct component_impl;
template <size_t I, class... Expr> struct component_impl<I, Vector<Expr...>> {
  using type = std::tuple_element_t<I, std::tuple<Expr...>>;
};
} // namespace detail

template <size_t I, class T>
using Component = typename detail::component_impl<I, T>::type;

namespace detail {
template <class T, class U> struct dot_impl {};
template <class... Expr1, class... Expr2>
struct dot_impl<Vector<Expr1...>, Vector<Expr2...>> {
  using type = std::enable_if_t<sizeof...(Expr1) == sizeof...(Expr2),
                                Sum<Multiplies<Expr1, Expr2>...>>;
};
} // namespace detail

template <class V1, class V2>
using Dot = typename detail::dot_impl<V1, V2>::type;
template <class V> using Norm2 = Dot<V, V>;
template <class V> using Norm = Power<Norm2<V>, Rational<1, 2>>;
} // namespace Expression

namespace detail {
template <class... Expr>
struct Eval<Expression::Negate<Expression::Vector<Expr...>>> {
  template <class T, class Args> static T eval(Args const &args) {
    return evaluate<T, Expression::Vector<Expression::Negate<Expr>...>>(args);
  }
};

template <class... Expr1, class... Expr2>
struct Eval<Expression::Plus<Expression::Vector<Expr1...>,
                             Expression::Vector<Expr2...>>> {
  template <class T, class Args> static T eval(Args const &args) {
    return evaluate<T, Expression::Vector<Expression::Plus<Expr1, Expr2>...>>(
        args);
  }
};

} // namespace detail
} // namespace mdx

#endif // OBSERVABLES_VECTOR_HPP

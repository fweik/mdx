#ifndef OBSERVABLES_VECTOR_HPP
#define OBSERVABLES_VECTOR_HPP

#include "arithmetic.hpp"
#include "expression.hpp"

#include <tuple>
#include <type_traits>

namespace mdx {
namespace Expression {
namespace Tags {
struct Vector;
template <size_t I> struct Component;
} // namespace Tags

template <class... Components> using Vector = Expr<Tags::Vector, Components...>;

template <size_t I, class Expr>
usign Component = Unary<Tags::Component<I>, Expr>;

namespace detail {
template <class T, class U> struct dot_impl {};
template <class... Expr1, class... Expr2>
struct dot_impl<Vector<Expr1...>, Vector<Expr2...>> {
  using type = Sum<Multiplies<Expr1, Expr2>...>;
};
} // namespace detail

template <class V1, class V2>
using Dot = typename detail::dot_impl<V1, V2>::type;
template <class V> using Norm2 = Dot<V, V>;
template <class V> using Norm = Power<Norm2<V>, Rational<1, 2>>;
} // namespace Expression

namespace Grammar {}

} // namespace mdx

#endif // OBSERVABLES_VECTOR_HPP

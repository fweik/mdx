#ifndef OBSERVABLES_VECTOR_HPP
#define OBSERVABLES_VECTOR_HPP

#include "arithmetic.hpp"
#include "expression.hpp"

#include <tuple>
#include <type_traits>

namespace mdx {
namespace Expression {
namespace Tags {
template <class... Components> struct Vector;
template <size_t I> struct Component;
} // namespace Tags

template <class... Components>
using Vector = Nullary<Tags::Vector<Components...>>;

template <size_t I, class Expr>
using Component = Unary<Tags::Component<I>, Expr>;

template <class...> constexpr bool is_vector = false;
template <class... Components>
constexpr bool is_vector<Vector<Components...>> = true;
} // namespace Expression

namespace Grammar {
template <class... Components> struct rule<Expression::Vector<Components...>> {
  using type = Expression::Vector<expand<Components>...>;
};

template <size_t I, class... Components>
struct rule<Expression::Component<I, Expression::Vector<Components...>>> {
  using component_expr = std::tuple_element_t<I, std::tuple<Components...>>;
  using type = expand<component_expr>;
};
} // namespace Grammar
} // namespace mdx

#endif // OBSERVABLES_VECTOR_HPP

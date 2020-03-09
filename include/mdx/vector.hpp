#ifndef OBSERVABLES_VECTOR_HPP
#define OBSERVABLES_VECTOR_HPP

#include "arithmetic.hpp"
#include "expression.hpp"

#include <array>
#include <tuple>
#include <type_traits>

namespace mdx {
namespace Expression {
  namespace Tags {
    template<class... Components>
    struct Vector;
    template<size_t I>
    struct Component;
  }// namespace Tags

  template<class... Components>
  using Vector = Nullary<Tags::Vector<Components...>>;

  template<size_t I, class Expr>
  using Component = Unary<Tags::Component<I>, Expr>;

  template<class...>
  struct is_vector : std::false_type
  {
  };
  template<class... Components>
  struct is_vector<Vector<Components...>> : std::true_type
  {
  };

  namespace detail {
    template<class, class, class = void>
    struct dot_impl;
    template<class... Components1, class... Components2>
    struct dot_impl<
      Vector<Components1...>,
      Vector<Components2...>,
      std::enable_if_t<sizeof...(Components1) == sizeof...(Components2)>>
    {
      using type = Sum<Product<Components1, Components2>...>;
    };
  }// namespace detail

  template<class Expr1, class Expr2>
  using Dot = typename detail::dot_impl<Expr1, Expr2>::type;
}// namespace Expression

namespace detail {
  template<class... Components>
  struct Eval<Expression::Vector<Components...>>
  {
    template<class T, class Args>
    static std::array<T, sizeof...(Components)> eval(Args const &args)
    {
      return { evaluate<T, Components>(args)... };
    }
  };
}// namespace detail

namespace Grammar {
  template<class... Components>
  struct rule<Expression::Vector<Components...>>
  {
    using type = Expression::Vector<expand<Components>...>;
  };

  template<size_t I, class... Components>
  struct rule<Expression::Component<I, Expression::Vector<Components...>>>
  {
    using component_expr = std::tuple_element_t<I, std::tuple<Components...>>;
    using type = expand<component_expr>;
  };
}// namespace Grammar
}// namespace mdx
#endif// OBSERVABLES_VECTOR_HPP

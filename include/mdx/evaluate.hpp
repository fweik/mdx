#ifndef OBSERVABLES_EVALUATE_HPP
#define OBSERVABLES_EVALUATE_HPP

#include "expression.hpp"

namespace mdx {
namespace detail {
  template<class Expr, class = void>
  struct Eval;

  template<class T, class Expr>
  struct Value;

  template<class>
  struct value_type;
  template<class T, class Expr>
  struct value_type<Value<T, Expr>>
  {
    using type = T;
  };
  template<class T>
  using value_type_t = typename value_type<T>::type;
}// namespace detail

template<class T, class Expr, class... Args>
auto evaluate(Args const &... args)
{
  return detail::Eval<Expr>::template eval<T>(std::make_tuple(args...));
}

template<class T, class Expr>
auto evaluate()
{
  return detail::Eval<Expr>::template eval<T>(std::make_tuple());
}

}// namespace mdx

#endif// OBSERVABLES_EVALUATE_HPP

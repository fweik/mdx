#ifndef MDX_ALGORITHMS_HPP
#define MDX_ALGORITHMS_HPP

#include "expression.hpp"

#include <type_traits>

namespace mdx {
namespace Algorithms {
  namespace detail {
    template<template<class, class> class BinaryOp, class Expr, class... Tail>
    struct right_fold_impl
    {
      using type =
        BinaryOp<Expr, typename right_fold_impl<BinaryOp, Tail...>::type>;
    };

    template<template<class, class> class BinaryOp, class Expr>
    struct right_fold_impl<BinaryOp, Expr>
    {
      using type = Expr;
    };
  }// namespace detail

  template<template<class, class> class BinaryOp, class... Expr>
  using right_fold = typename detail::right_fold_impl<BinaryOp, Expr...>::type;
}// namespace Algorithms
}// namespace mdx

#endif// MDX_ALGORITHMS_HPP

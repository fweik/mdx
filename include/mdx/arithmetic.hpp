#ifndef OBSERVABLES_ARITHMATIC_HPP
#define OBSERVABLES_ARITHMATIC_HPP

#include "evaluate.hpp"
#include "expression.hpp"

namespace mdx {
namespace Expression {
namespace Tags {
struct Negate;
struct Multiplies;
struct Plus;
struct Divides;
struct Power;
} // namespace Tags

/**
 * @brief Negatation expression.
 *
 * f(x) = -x
 */
template <class Arg> using Negate = Unary<Tags::Negate, Arg>;

/**
 * @brief Product expression.
 *
 * f(x, y) = x * y
 */
template <class Arg1, class Arg2>
using Multiplies = Binary<Tags::Multiplies, Arg1, Arg2>;

/**
 * @brief Sum expression.
 *
 * f(x, y) = x + y
 */
template <class Arg1, class Arg2> using Plus = Binary<Tags::Plus, Arg1, Arg2>;

/**
 * @brief Division expression.
 *
 * f(x, y) = x / y
 */
template <class Arg1, class Arg2>
using Divides = Binary<Tags::Divides, Arg1, Arg2>;

/**
 * @brief Power expression.
 *
 * f(x, y) = x^y
 */
template <class Arg1, class Arg2> using Power = Binary<Tags::Power, Arg1, Arg2>;

/**
 * @brief Sum expression.
 *
 * f(x1, ... xn) = x1 + ... + xn
 *
 */
template <class... Expr> using Sum = left_fold<Plus, Expr...>;

/**
 * @brief Product expression.
 *
 * f(x1, ... xn) = x1 * ... * xn
 *
 */
template <class... Expr> using Product = left_fold<Multiplies, Expr...>;
} // namespace Expression

namespace detail {
template <class Arg> struct Eval<Expression::Negate<Arg>> {
  template <class T, class Args> static T eval(Args const &args) {
    return -evaluate<T, Arg>(args);
  }
};

template <class Arg1, class Arg2> struct Eval<Expression::Plus<Arg1, Arg2>> {
  template <class T, class Args> static T eval(Args const &args) {
    return evaluate<T, Arg1>(args) + evaluate<T, Arg2>(args);
  }
};

template <class Arg1, class Arg2>
struct Eval<Expression::Multiplies<Arg1, Arg2>> {
  template <class T, class Args> static T eval(Args const &args) {
    return evaluate<T, Arg1>(args) * evaluate<T, Arg2>(args);
  }
};
} // namespace detail

} // namespace mdx
#endif // OBSERVABLES_ARITHMATIC_HPP

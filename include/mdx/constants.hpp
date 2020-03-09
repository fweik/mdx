#ifndef OBSERVABLES_CONSTANTS_HPP
#define OBSERVABLES_CONSTANTS_HPP

#include "arithmetic.hpp"
#include "evaluate.hpp"
#include "expression.hpp"

namespace mdx {
namespace Expression {
namespace Tags {
template <class Integral, Integral> struct Constant;
template <class STag> struct Symbol;
} // namespace Tags

/**
 * @brief Constant expression that represents an integral number.
 *
 * @tparam value Value of the constant.
 */
template <int value> using Integer = Nullary<Tags::Constant<int, value>>;

/**
 * @brief Rational Number expression.
 */
template <int nominator, int denominator>
using Rational = Divides<Integer<nominator>, Integer<denominator>>;

/**
 * @brief Symbol.
 *
 * @tparam T Identifier of the symbol.
 */
template <class T> using Symbol = Nullary<Tags::Symbol<T>>;

/**
 * @brief Variable.
 *
 * @tparam c Signel character name for the variable.
 */
template <char c> using Variable = Symbol<std::integral_constant<char, c>>;

namespace Variables {
using X = Variable<'x'>;
using Y = Variable<'y'>;
using Z = Variable<'z'>;
} // namespace Variables
} // namespace Expression

namespace detail {
template <class T, class Symbol> struct Value { T val; };

template <int val> struct Eval<Expression::Integer<val>> {
  template <class T, class Args> static T eval(Args) { return val; }
};

template <class STag> struct Eval<Expression::Symbol<STag>> {
  template <class T, class Args> static T eval(Args const &args) {
    return std::get<Value<T, Expression::Symbol<STag>>>(args).val;
  }
};
} // namespace detail

template <class Symbol, class T> detail::Value<T, Symbol> value(T const &val) {
  return {val};
}

} // namespace mdx

#endif // OBSERVABLES_CONSTANTS_HPP

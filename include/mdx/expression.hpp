#ifndef OBSERVABLES_META_HPP
#define OBSERVABLES_META_HPP

namespace mdx {
namespace Expression {
/**
 * @brief Expression type
 * An expression is just a tag type and zero
 * or more argument expressions.
 */
template <class Tag, class... SubExpr> struct Expr;
template <class Tag> using Nullary = Expr<Tag>;
template <class Tag, class Arg> using Unary = Expr<Tag, Arg>;
template <class Tag, class Arg1, class Arg2>
using Binary = Expr<Tag, Arg1, Arg2>;

/**
 * @brief Number of argument of an expression.
 */
template <class> size_t arity;
template <class Tag, class... Args>
constexpr size_t arity<Expr<Tag, Args...>> = sizeof...(Args);
} // namespace Expression

namespace Grammar {
template <class Expr> struct rule;

/* Apply grammar rules */
template <class Expr> using expand = typename rule<Expr>::type;

/**
 * @brief Recursion rule for expressions with sub-expressions
 */
template <class Tag, class... SubExpr>
struct rule<Expression::Expr<Tag, SubExpr...>> {
  using type = Expression::Expr<Tag, expand<SubExpr>...>;
};
} // namespace Grammar
}; // namespace mdx
#endif

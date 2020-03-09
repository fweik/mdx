#define BOOST_TEST_MODULE observables_test
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <observables/constants.hpp>

using namespace mdx;

BOOST_AUTO_TEST_CASE(Integer_) {
  using namespace Expression;

  static_assert(arity<Integer<5>> == 0, "");
  static_assert(is_expr<Integer<5>>, "");
}

BOOST_AUTO_TEST_CASE(Symbol_) {
  using namespace Expression;

  static_assert(arity<Symbol<int>> == 0, "");
  static_assert(is_expr<Symbol<int>>, "");
}

BOOST_AUTO_TEST_CASE(eval_integer_) {
  using namespace Expression;

  using Expr = Integer<5>;

  auto const result = evaluate<int, Expr>();

  BOOST_CHECK_EQUAL(result, 5);
}

BOOST_AUTO_TEST_CASE(eval_symbol_) {
  using namespace Expression::Variables;

  auto const result = evaluate<int, X>(value<X>(5));
  BOOST_CHECK_EQUAL(result, 5);
}
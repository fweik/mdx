#define BOOST_TEST_MODULE mdx
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <mdx/constants.hpp>

using namespace mdx;

BOOST_AUTO_TEST_CASE(eval_integer_)
{
  using namespace Expression;
  constexpr int test_value = 5;

  using Expr = Integer<test_value>;

  auto const result = evaluate<int, Expr>();

  BOOST_CHECK_EQUAL(result, test_value);
}

BOOST_AUTO_TEST_CASE(eval_symbol_)
{
  using namespace Expression::Variables;

  auto const result = evaluate<int, X>(value<X>(5));
  BOOST_CHECK_EQUAL(result, 5);
}
#define BOOST_TEST_MODULE mdx
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <mdx/arithmetic.hpp>
#include <mdx/constants.hpp>

BOOST_AUTO_TEST_CASE(eval_plus_)
{
  using namespace mdx::Expression;
  using mdx::evaluate;

  using Expr = Plus<Integer<1>, Integer<2>>;
  auto const result = evaluate<int, Expr>();

  BOOST_CHECK_EQUAL(result, 3);
}

BOOST_AUTO_TEST_CASE(eval_multiplies_)
{
  using namespace mdx::Expression;
  using mdx::evaluate;

  using Expr = Multiplies<Integer<2>, Integer<3>>;
  auto const result = evaluate<int, Expr>();

  BOOST_CHECK_EQUAL(result, 6);
}

template<class T, class U>
constexpr bool is_same = std::is_same<T, U>::value;

BOOST_AUTO_TEST_CASE(sum_expr_)
{
  using namespace mdx::Expression;
  using namespace Variables;

  static_assert(is_same<Sum<X, Y, Z>, Plus<X, Plus<Y, Z>>>, "");
}

BOOST_AUTO_TEST_CASE(product_expr_)
{
  using namespace mdx::Expression;
  using namespace Variables;

  static_assert(is_same<Product<X, Y, Z>, Multiplies<X, Multiplies<Y, Z>>>, "");
}

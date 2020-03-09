#define BOOST_TEST_MODULE mdx_test
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <mdx/constants.hpp>
#include <mdx/evaluate.hpp>
#include <mdx/vector.hpp>

using namespace mdx::Expression;

BOOST_AUTO_TEST_CASE(is_vector_)
{
  static_assert(is_vector<Vector<>>, "");
  static_assert(not is_vector<int>, "");
}

template<class T, class U>
constexpr bool is_same = std::is_same<T, U>::value;
template<class T, class U>
constexpr bool expands_to = is_same<mdx::Grammar::expand<T>, U>;

BOOST_AUTO_TEST_CASE(component_)
{
  using V = Vector<Integer<0>, Integer<1>, Integer<2>>;
  static_assert(expands_to<Component<0, V>, Integer<0>>, "");
  static_assert(expands_to<Component<1, V>, Integer<1>>, "");
  static_assert(expands_to<Component<2, V>, Integer<2>>, "");
}

BOOST_AUTO_TEST_CASE(dot_expr_)
{
  using namespace Variables;

  using V1 = Vector<U, V, W>;
  using V2 = Vector<X, Y, Z>;

  static_assert(
    expands_to<Dot<V1, V2>, Sum<Product<U, X>, Product<V, Y>, Product<W, Z>>>,
    "");
}

BOOST_AUTO_TEST_CASE(vector_eval_)
{
  using V = Vector<Integer<2>, Integer<3>, Integer<4>>;

  auto const result = mdx::evaluate<double, V>();
  BOOST_CHECK_EQUAL(result[0], double(2));
  BOOST_CHECK_EQUAL(result[1], double(3));
  BOOST_CHECK_EQUAL(result[2], double(4));
}

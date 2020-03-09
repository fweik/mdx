#define BOOST_TEST_MODULE mdx_test
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <mdx/constants.hpp>
#include <mdx/evaluate.hpp>
#include <mdx/vector.hpp>

using namespace mdx::Expression;

BOOST_AUTO_TEST_CASE(is_vector_) {
  static_assert(is_vector<Vector<>>, "");
  static_assert(not is_vector<int>, "");
}

template <class T, class U> constexpr bool is_same = std::is_same<T, U>::value;

BOOST_AUTO_TEST_CASE(component_access_) {
  using V = Vector<Integer<0>, Integer<1>, Integer<2>>;
  static_assert(is_same<Integer<0>, mdx::Grammar::expand<Component<0, V>>>, "");
  static_assert(is_same<Integer<1>, mdx::Grammar::expand<Component<1, V>>>, "");
  static_assert(is_same<Integer<2>, mdx::Grammar::expand<Component<2, V>>>, "");
}

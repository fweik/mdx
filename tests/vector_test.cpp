#define BOOST_TEST_MODULE observables_test
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <observables/constants.hpp>
#include <observables/evaluate.hpp>
#include <observables/vector.hpp>

using namespace mdx::Expression;

BOOST_AUTO_TEST_CASE(is_vector_) {
  static_assert(is_vector<Vector<>>, "");
  static_assert(not is_vector<int>, "");
}

template <class T, class U> constexpr bool is_same = std::is_same<T, U>::value;

BOOST_AUTO_TEST_CASE(component_access_) {
  using V = Vector<Integer<0>, Integer<1>, Integer<2>>;
  static_assert(is_same<V::X, Component<0, V>>, "");
  static_assert(is_same<V::Y, Component<1, V>>, "");
  static_assert(is_same<V::Z, Component<2, V>>, "");

  static_assert(is_same<V::X, Integer<0>>, "");
  static_assert(is_same<V::Y, Integer<1>>, "");
  static_assert(is_same<V::Z, Integer<2>>, "");
}

BOOST_AUTO_TEST_CASE(dot_expr_) {
  using V1 = Vector<Integer<1>, Integer<2>>;
  using V2 = Vector<Integer<3>, Integer<4>>;

  using R = Dot<V1, V2>;

  static_assert(
      is_same<R, Plus<Multiplies<V1::X, V2::X>, Multiplies<V1::Y, V2::Y>>>, "");
}

BOOST_AUTO_TEST_CASE(norm2_expr_) {
  using V = Vector<Integer<1>, Integer<2>>;
  using R = Norm2<V>;

  static_assert(
      is_same<R, Plus<Multiplies<V::X, V::X>, Multiplies<V::Y, V::Y>>>, "");
}

BOOST_AUTO_TEST_CASE(eval_nagate_) {
  using namespace mdx::Expression;
}
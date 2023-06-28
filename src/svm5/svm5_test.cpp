#include <nil/crypto3/algebra/curves/pallas.hpp>

using namespace nil::crypto3::algebra::curves;

typename pallas::base_field_type::value_type
foo(typename pallas::base_field_type::value_type a) {
  return a;
}

[[circuit]] typename pallas::base_field_type::value_type
svm(typename pallas::base_field_type::value_type x1,
    typename pallas::base_field_type::value_type x2,
    typename pallas::base_field_type::value_type x3,
    typename pallas::base_field_type::value_type x4,
    typename pallas::base_field_type::value_type x5) {

  // ret + w_i * x_i
  typename pallas::base_field_type::value_type ret = 0;
  ret = ret + (1 * x1);
  ret = ret + (2 * x2);
  ret = ret + (1 * x3);
  ret = ret + (3 * x4);
  ret = ret + (1 * x5);

  foo(ret);

  return -1;
}

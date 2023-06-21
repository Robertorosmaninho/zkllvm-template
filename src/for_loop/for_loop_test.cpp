#include <nil/crypto3/algebra/curves/pallas.hpp>

#define N 2

using namespace nil::crypto3::algebra::curves;

[[circuit]] typename pallas::base_field_type::value_type
  add(typename pallas::base_field_type::value_type a,
      typename pallas::base_field_type::value_type b) {
  typename pallas::base_field_type::value_type arr[N];
  for (std::size_t i = 0; i < N; i++) {
    arr[i] = a+b;
  }
  return arr[0] + arr[1];
}
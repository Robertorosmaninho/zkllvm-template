// Modified from the transfer function at
//   https://docs.soliditylang.org/en/v0.8.17/contracts.html

#include <nil/crypto3/algebra/curves/pallas.hpp>

#define ITER 10
//#define ITER 1000
//#define ITER 5000

using namespace nil::crypto3::algebra::curves;

typename pallas::base_field_type::value_type balanceSender = 10000000;
typename pallas::base_field_type::value_type balanceTo = 200;
typename pallas::base_field_type::value_type amount = 10;
bool res = 0;

[[circuit]] typename pallas::base_field_type::value_type
  transfer(typename pallas::base_field_type::value_type addressTo) {

  std::size_t iter = 5000; // MAX: a million transfers
  std::size_t j = 0;
  while (j < iter) {
    balanceSender = balanceSender - amount;
    balanceTo = balanceTo + amount;
    res = 1; // transfer is successful
    j = j + 1;
  }

  return 0;
}

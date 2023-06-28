// Modified from the transfer function at
//   https://docs.soliditylang.org/en/v0.8.17/contracts.html

#include <nil/crypto3/algebra/curves/pallas.hpp>

using namespace nil::crypto3::algebra::curves;

typename pallas::base_field_type::value_type balanceSender = 100;
typename pallas::base_field_type::value_type balanceTo = 200;
typename pallas::base_field_type::value_type amount = 10;

[[circuit]] typename pallas::base_field_type::value_type
  transfer(typename pallas::base_field_type::value_type addressTo) {

  balanceSender = balanceSender - amount;
  balanceTo = balanceTo + amount;
  return 1; // transfer is successful

}

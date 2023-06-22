#define ZKLLVM

#ifdef ZKLLVM
#include <nil/crypto3/algebra/curves/pallas.hpp>
#endif

#include "unit_tests.hpp"

#ifdef ZKLLVM
using namespace nil::crypto3::algebra::curves;

[[circuit]] typename pallas::base_field_type::value_type
circuit_main(typename pallas::base_field_type::value_type a,
             typename pallas::base_field_type::value_type b) {

  testLinkedList();
  testVector();
  //testMap();
  testDeque();

  return a + b;
}
#endif

#ifndef ZKLLVM
int main() {
  testLinkedList();
  std::cout << std::endl;
  testVector();
  std::cout << std::endl;
  testMap();
  std::cout << std::endl;
  testDeque();
  return 0;
}
#endif
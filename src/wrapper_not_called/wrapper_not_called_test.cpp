#include <cstdlib>

//[[circuit]]
int add(int a, int b) {
  return a + b;
}

[[circuit]] int mul(int a, int b) {
  return a * b;
}

// This is a wrapper function that reads from a file and call the circuit
// function with the correct inputs that we want to pass.
int main(int argv, char **argc) {
  int a = atoi(argc[1]) + 10;
  int b = atoi(argc[2]) + 5;
  return mul(a, b);
}

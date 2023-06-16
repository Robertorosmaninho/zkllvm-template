int global_a = 5;
int global_b = 8;

struct S {
  int i;
  int j;
};

[[circuit]] int add(int a, int b) {
    struct S s = { global_a, global_b};
    return a + b + s.i + s.j;
}

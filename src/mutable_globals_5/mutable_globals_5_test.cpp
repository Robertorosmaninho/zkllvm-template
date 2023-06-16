int global_a = 5;
int global_b = 8;

struct S {
  int i;
  int j;
};

int aux_add(struct S arg) {
  return arg.i + arg.j;
}

[[circuit]] int add(int a, int b) {
    struct S s = { global_a, global_b };
    s.i = s.i + a;
    s.j = s.j + b;
    return aux_add(s);
}

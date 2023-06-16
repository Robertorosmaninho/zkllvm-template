int global_a = 5;

struct S {
  int i;
  int j;
};

int aux_add(struct S arg) {
  return arg.i + arg.j;
}

struct S aux_update_struct(struct S arg) {
  struct S s = { arg.i + 1, arg.j + 2 };
  return s;
}

[[circuit]] int add(int a, int b) {
  struct S s = { global_a, global_a };
  return aux_add(aux_update_struct(s));
}

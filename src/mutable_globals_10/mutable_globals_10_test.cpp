#include <stdlib.h>

int global_a = 5;

struct S {
  int i;
  int j;
};

int aux_add(struct S *arg) {
  return arg->i + arg->j;
}

void aux_update_struct(struct S *arg) {
  arg->i = arg->i + 1;
  arg->j = arg->j + 2;
}

[[circuit]] int add(int a, int b) {
  struct S *s = (struct S*)malloc(sizeof(struct S));
  s->i = a;
  s->j = b;
  aux_update_struct(s);
  return aux_add(s);
}

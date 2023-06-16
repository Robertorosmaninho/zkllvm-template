#include <stdlib.h>

int global_a = 5;

struct S {
  int i;
  int j;
};

int aux_add(struct S *arg) {
  return arg->i + arg->j;
}

[[circuit]] int add(int a, int b) {
  struct S *s = (struct S*)malloc(sizeof(struct S));
  s->i = a;
  s->j = b;
  return aux_add(s);
}

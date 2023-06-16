It works for gcc and clang, but not for zkLLVM clang.

```
bitcast
terminate called after throwing an instance of 'std::bad_cast'
  what():  std::bad_cast
```

Clang simply ignores the unknown attribute circuit.

$> clang main.c
main.c:65:16: warning: unknown attribute 'circuit' ignored [-Wunknown-attributes]
__attribute__((circuit)) int verify(int a, int b) {
               ^~~~~~~
1 warning generated.
$> ./a.out 01010010 01010110

$> echo $?
0

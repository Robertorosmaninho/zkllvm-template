int global_a = 0;
int global_b = 0;

[[circuit]] int mul(int a, int b) {
    return global_a * global_b;
}

int global_a = 1;

[[circuit]] int add(int a, int b) {
    global_a = b + global_a;
    return a + b + global_a;
}

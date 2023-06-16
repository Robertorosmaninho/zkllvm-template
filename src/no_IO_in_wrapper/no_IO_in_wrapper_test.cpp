#include <cstdio>

[[circuit]] int add(int a, int b) {
    return a + b;
}

// This is a wrapper function that reads from a file and call the circuit
// function with the correct inputs that we want to pass.
int main(int argv, char **argc) {
    int a, b;
    FILE *file = fopen(argc[1], "r");
    if (file == NULL) {
        printf("Error: File not found\n");
        return 1;
    }
    fscanf(file,"%d", &a);
    fscanf(file,"%d", &b);
    fclose(file);
    return add(a, b);
}

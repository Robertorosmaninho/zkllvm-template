#include <cstdio>
#include <cstdlib>

[[circuit]] int verify(int a, int b) {
    char bin_r[10];
    sprintf(bin_r, "%d", a);
    char bin_v[10];
    sprintf(bin_v, "%d", b);

    char r = strtol(bin_r, NULL, 2);
    char v = strtol(bin_v, NULL, 2);

    if (r == 'R' && v == 'V')
        return 0;

    return 1;
}

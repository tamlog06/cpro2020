#include <stdio.h>

int main() {
    float a, b = 0;
    double c, d = 0;

    for (int i = 0; i < 1e+8; i++) {
        a+= 1e-8;
        c+= 1e-8;
    }

    b = 1e-8 * 1e+8;
    d = 1e-8 * 1e+8;

    printf("a = %.20f\nb = %.20f\nc = %.20f\nd = %.20f\n", a, b, c, d);
    return 0;
}
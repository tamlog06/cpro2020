#include <stdio.h>

float my_abs(float x) {
    if (x >= 0) {
        return x;
    } else {
        return -x;
    }
}

int main() {
    float x = 1;
    int i;
    for (i = 0; i < 10; i++) {
        x = x - 1.0 / 3.0;
        if (my_abs(x) <= 1e-8) {
            break;
        }
        printf("%f\n", x);
    }
    return 0;
}
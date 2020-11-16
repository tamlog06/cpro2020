#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_oct(int m, int n, const float *x, const char *name) {
    printf("%s = [ ", name);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++){
            printf(" %.4f", x[i * n + j]);
        }
        printf(" ;\n");
    }
    printf("];\n");
}

void mul(int m, int n, const float *x, const float *A, float *o) {
    for (int k = 0; k < m; k++) {
        float sum = 0.0;
        for (int i = 0; i < n; i++) {
            sum += (A[k * n + i] * x[i]);
        }
        o[k] = sum;
    }
}

int main() {
    float A[6] = {1, 2, 3, 4, 5, 6};
    float x[3] = {2, 3, 5};
    float o[2];
    mul(2, 3, x, A, o);
    print_oct(2, 3, A, "A");
    print_oct(3, 1, x, "x");
    print_oct(2, 1, o, "o");
    return 0;
}
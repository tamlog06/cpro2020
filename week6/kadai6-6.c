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

void rand_init(int n, float *o) {
    int vmin = -1;
    int vmax = 1;
    double vrange = vmax - vmin;
    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        o[i] = vmin + (float)(rand() * vrange / (1.0 + RAND_MAX));
    }
}

int main() {
    float y[6];
    // 初期化前の値
    print_oct(2, 3, y, "y");
    rand_init(6, y);
    // 初期化後の値
    print_oct(2, 3, y, "y");
    return 0;
}
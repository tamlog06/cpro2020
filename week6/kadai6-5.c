#include <stdio.h>

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

void init(int n, float x, float *o) {
    for (int i = 0; i < n; i++) {
        o[i] = x;
    }
}

int main() {
    float y[6];
    // 初期化前の値
    print_oct(2, 3, y, "y");
    init(6, 7, y);
    // 初期化後の値
    print_oct(2, 3, y, "y");
    return 0;
}
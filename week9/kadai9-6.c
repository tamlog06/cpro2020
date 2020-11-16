#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdint.h>
#include <assert.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <string.h>
#include <time.h>

void print(int m, int n, const float *x) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++){
            printf("%.4f ", x[i * n + j]);
        }
        printf("\n");
    }
}

void load(const char *filename, int m, int n, float *A, float *b) {
    FILE *fp = NULL;
    fp = fopen("test.dat", "r");
    fread(A, sizeof(float), n * m, fp);
    fread(b, sizeof(float), m, fp);
    fclose(fp);
}

int main(int argc, char *argv[]) {
    int n,m = 0;
    if (argc > 1) {
        n = atoi(argv[1]);
        m = atoi(argv[2]);
    }
    float *A = malloc(sizeof(float) * n*m);
    float *b = malloc(sizeof(float) * m);

    load("test.dat", m, n, A, b);
    print(m, n, A);
    print(m, 1, b);
    return 0;
}
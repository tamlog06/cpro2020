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

void rand_init(int n, float *o) {
    int vmin = -1;
    int vmax = 1;
    double vrange = vmax - vmin;
    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        o[i] = vmin + (float)(rand() * vrange / (1.0 + RAND_MAX));
    }
}

void print(int m, int n, const float *x) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++){
            printf("%.4f ", x[i * n + j]);
        }
        printf("\n");
    }
}

void swap(float *pa, float *pb){
    float temp = *pa;
    *pa = *pb;
    *pb = temp;
}

void sort(float a[], int n) {
    int i, j;
    int num = 0;

    for (i = n-1; i > 0; i--) {
        for (j = 0; j < i; j++) {
            if (a[j] > a[j+1]) {
                swap(&a[j], &a[j+1]);
            }
            num++;
        }
    }
}

void softmax(int n, const float * x, float * y) {
    float xmax = 0;
    float sum = 0;
    for (int i = 0; i < n; i++) {
        if (x[i] > xmax) {
            xmax = x[i];
        }
    }

    for (int i = 0; i < n; i++) {
        sum += exp(x[i] - xmax);
    }

    for (int k = 0; k < n; k++) {
        y[k] = exp(x[k] - xmax) / sum;
    }
}

int main(int argc, char *argv[]) {
    int n = 0;
    if (argc > 1) {
        n = atoi(argv[1]);
    }
    float *y = malloc(sizeof(float) * n);
    rand_init(n, y);
    print(1, n, y);
    softmax(n, y, y);
    print(1, n, y);
    return 0;}
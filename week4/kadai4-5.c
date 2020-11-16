#include <stdio.h>

int input() {
    int n,i;
    printf("n = ");
    i = scanf("%d", &n);
    do {
        if(i != 1 || n < 0) {
            printf("Invalid input\n");
            scanf("%*s");
            printf("n = ");
            i = scanf("%d", &n); 
            }
    } while (i != 1 || n < 0);
}

int fact(int n) {
    int fact_n = 1;
    for (int i = 1; i < n+1; i++) {
        fact_n *= i;
    }
    return fact_n;
}

int perm(int n, int r) {
    return fact(n) / fact(n - r);
}

int main(int n) {
    n = input();
    for (int i = 0; i < n+1;i++) {
        printf("perm(%d,%d) = %d\n", n, i, perm(n, i));
    }
    return 0;
}
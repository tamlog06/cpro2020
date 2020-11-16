#include <stdio.h>

int main() {
    int n, fact_n;
    printf("n:");
    scanf("%d", &n);
    fact_n = 1;

    for (int i=1; i <= n; i++) {
        fact_n *= i;
    }
    printf("n!=%d", fact_n);
    return 0;
}
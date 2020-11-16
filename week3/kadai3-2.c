#include <stdio.h>

int main() {
    int n, fact_n;
    fact_n = 1;
    printf("n:");
    scanf("%d", &n);

    while (n > 0) {
        fact_n *= n;
        n -= 1;
    }

    printf("n!=%d", fact_n);
    return 0;
}
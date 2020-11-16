#include <stdio.h>

int input(char x) {
    int n=-1 ,i;

    do {
        printf("%c = ", x);
        i = scanf("%d", &n);

        if(i != 1) {
            printf("Invalid input\n");
            scanf("%*s");
        } else if (n < 0) {
            printf("Invalid input\n");
        }
    } while (n < 0);

    return n;
}

int comb(int n, int r) {
    if (r == 0 || r == n) {
        return 1;
    } else if (r == 1) {
        return n;
    } else {
        return comb(n - 1, r - 1) + comb(n - 1, r);
    }
}

int main(void) {
    int n = input('n');
    int r = input('r');

    /* r > n の場合はエラー */
    while (r > n) {
        printf("Invalid input: r must be smaller than n\n");
        n = input('n');
        r = input('r');
    }

    printf("%d\n", comb(n, r));
    return 0;
}


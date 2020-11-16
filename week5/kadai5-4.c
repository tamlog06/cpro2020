#include <stdio.h>

int input() {
    int n=-1 ,i;

    do {
        printf("n = ");
        i = scanf("%d", &n);

        if(i != 1) {
            printf("Invalid input\n");
            scanf("%*s");
        } 
    } while (i != 1);

    return n;
}

void display(int n) {
    int len = 32;
    int bit[32];
    int x;

    for(int i = 0; i < len; i++) {
        x = 1 << i;
        x = n & x;
        bit[len - i - 1] = x >> i;
    }

    if (n < 0) {
        bit[0] = 1;
    }

    printf("%d (10) = ", n);

    for(int i = 0; i < len; i++) {
        printf("%d", bit[i]);
    }

    printf(" (2)");
}


int main() {
    int n = input();
    display(n);
    return 0;
}
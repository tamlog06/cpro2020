#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/* 関数histを自分で作成 */
void hist(int n) {
    srand(time(NULL));
    int x;
    int vmin = 0;
    int vmax = 9;
    double vrange = vmax - vmin + 1;
    double count[10] = {0,0,0,0,0,0,0,0,0,0};

    for (int i = 1; i < n + 1; i++) {
        x = vmin + (int)(rand() * vrange / (1.0 + RAND_MAX));
        count[x]++;
    }

    printf("n=%7d:", n);

    for (int i = 0; i < 10;i++) {
        count[i] = count[i]/n*100;
        printf("  %4.1f", count[i]);
    }
    printf("\n");
}


int main() {
    hist(10);
    hist(100);
    hist(1000);
    hist(10000);
    hist(100000);
    hist(1000000);
    return 0;
} 

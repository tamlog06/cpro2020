#include <stdio.h>

void minmax(int data[], int *min, int *max) {
    for (int i = 0; i < 3; i++ ){
        if (data[i] < *min) {
            *min = data[i];
        }
        if (data[i] > *max) {
            *max = data[i];
        }
    }
}

int main() {
    int a[3];
    int min;
    int max;
    printf("input 1st integer : ");
    scanf("%d", &a[0]);
    printf("input 2nd integer : ");
    scanf("%d", &a[1]);
    printf("input 3rd integer : ");
    scanf("%d", &a[2]);

    // とりあえず最小値最大値をa[0]で初期化
    min = a[0];
    max = a[0];

    minmax(a, &min, &max);

    printf("min: %d, max: %d", min, max);

    return 0;
}
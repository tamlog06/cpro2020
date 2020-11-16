#include <stdio.h>
#define NUMBER 6

void swap(int *pa, int *pb){
    int temp = *pa;
    *pa = *pb;
    *pb = temp;
}

void bsort(int a[], int n) {
    int i, j;
    int num = 0;

    for (i = n-1; i > 0; i--) {
        for (j = 0; j < i; j++) {
            if (a[j] > a[j+1]) {
                swap(&a[j], &a[j+1]);
            }
            }
            num++;
            printf("\nloop%d:", num);
            for (j = 0; j < n; j++)
            {
                printf(" %d", a[j]);
        }
    }
}

int main(void) {
    int i;
    int Data[NUMBER];

    printf("Data: ");
    for (i = 0; i < NUMBER; i++) {
        scanf("%d", &Data[i]);
    }
    printf("N: 6");

    bsort(Data, NUMBER);
    return 0;
}
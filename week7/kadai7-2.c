#include <stdio.h>

int main() {
    char str[] = "Sun";
    int n[] = {10, 20, 40};
    double m[] = {1.5, 3.5, 7.5};
    for (int i = 0; i < 3; i++) {
        printf("value: %c, address: %p\n", str[i], &str[i]);
    }
    for (int i = 0; i < 3; i++) {
        printf("value: %d, address: %p\n", n[i], &n[i]);
    }
    for (int i = 0; i < 3; i++) {
        printf("value: %lf, address: %p\n", m[i], &m[i]);
    }
    return 0;
}
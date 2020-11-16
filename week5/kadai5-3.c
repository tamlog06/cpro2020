#include <stdio.h>

int main() {
    char a = 'a';
    printf("%c %d %x\n", a, a, a);
    a += 1;
    printf("%c %d %x", a, a, a);
    return 0;
}
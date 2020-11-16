#include <stdio.h>

int main() {
    int len = 0;
    char word[128];
    printf("Input a word: ");
    scanf("%s", word);
    while (word[len]) {
        if (word[len] == 122) {
            word[len] = 97;
        } else if (word[len] == 90) {
            word[len] = 65;
        } else {
            word[len]++;
        }
        len++;
    }
    printf("%s\n", word);
    return 0;
}
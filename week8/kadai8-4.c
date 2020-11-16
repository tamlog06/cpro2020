#include <stdio.h>

int main() {
    FILE *fp_r = NULL, *fp_w = NULL;
    char word[128];

    fp_r = fopen("test.txt", "r");
    fp_w = fopen("copy.txt", "w");
    if(!fp_r){
        printf("File cannot open.\n");
        return 0;
    }
    while (fgets(word, 128, fp_r)!= NULL) {
        fputs(word, fp_w);
    }

    fclose(fp_r);
    fclose(fp_w);
    return 0;
}
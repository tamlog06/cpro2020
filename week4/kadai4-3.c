#include <stdio.h>
#include <stdlib.h>

/* 関数my_absを自分で作成 */
float my_abs(float x) {
    /* x>=0 ならそのまま，それ以外なら-x */
    if (x >= 0) {
        return x;
    } else {
        return -x;
    }
}

int main() {
    float x = -1.3;
    float y = 3.7;
    float abs_x = my_abs(x);
    float abs_y = my_abs(y);
    printf("|x|=%f\n", abs_x);
    printf("|y|=%f\n", abs_y);
    return 0;
}
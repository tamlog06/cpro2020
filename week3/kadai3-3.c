#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main() {
    int user;
    printf("Your input (0, 2, 5): ");
    scanf("%d", &user);
    printf("\n");

    /* 入力が不適切なら再入力を促す */
    while (user != 0 && user != 2 && user != 5) {
        printf("Invalid input => Input again.\n");
        printf("Your input (0, 2, 5): ");
        scanf("%d", &user);
        printf("\n");
    }

    /* CPUの出目をランダムに選択 */
    /* mod3の値をそれぞれ対応させる */
    int cpu;
    int cpu_range = 3;
    srand(time(NULL));
    cpu = (rand() % cpu_range);
    if (cpu == 1) {
        cpu = 2;
    }
    else if (cpu == 2) {
        cpu = 5;
    }

    /* あいこなら再勝負 */
    while (cpu == user) {
        printf("Comp:%d vs You:%d => Try again\n", cpu, user);
        printf("Your input (0, 2, 5): ");
        scanf("%d", &user);
        printf("\n");

        /* 入力が不適切なら再入力を促す */
        while (user != 0 && user != 2 && user != 5) {
            printf("Invalid input => Input again.\n");
            printf("Your input (0, 2, 5): ");
            scanf("%d", &user);
            printf("\n");
        }

        /* CPUの出目をランダムに選択 */
        /* mod3の値をそれぞれ対応させる */
        cpu = (rand() % cpu_range);
        if (cpu == 1) {
            cpu = 2;
            }
        else if (cpu == 2) {
            cpu = 5;
            }
    }

    if ((cpu == 0 && user == 2) || (cpu == 2 && user == 5) || (cpu == 5 && user == 0)) {
        printf("Comp:%d vs You:%d => Comp win.\n", cpu, user);
    }
    else {
        printf("Comp:%d vs You:%d => You win.\n", cpu, user);
    }
    return 0;
}
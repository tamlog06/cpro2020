#include <stdio.h>
#include <math.h>

int main() {
    double a = 1.0;
    double b = 1.0e15;
    double c = 1.0e14;

    double x1 = (-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
    double x2 = (2 * c) / (-b - sqrt(pow(b, 2) - 4 * a * c));

    printf("method1: x = %f\n", x1);
    printf("method2: x = %f\n", x2);

    return 0;
}
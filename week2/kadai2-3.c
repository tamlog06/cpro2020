#include <stdio.h>
#include <math.h>
#include <complex.h>

int main() {
    double a,b,c;
    scanf("%lf", &a);
    scanf("%lf", &b);
    scanf("%lf", &c);

    double D = pow(b, 2) - 4 * a * c;
    if (D > 0) {
        D = sqrt(D);
        printf("%f\n%f\n", (-b + D) / (2 * a), (-b - D) / (2 * a));
    } else if (D == 0) {
        printf("%f\n", -b / (2 * a));
    } else {
        D = sqrt(-D);
        double _Complex z1 = (-b + D * I) / (2 * a);
        double _Complex z2 = (-b - D * I) / (2 * a);
        printf("%f+%f*I\n%f%f*I\n", creal(z1), cimag(z1), creal(z2), cimag(z2));
    }

}


#include <stdio.h>
#include <math.h>

int main() {
    double a,b,c;
    scanf("%lf", &a);
    scanf("%lf", &b);
    scanf("%lf", &c);
    
    double D;
    D = sqrt(pow(b, 2) - 4 * a * c);

    printf("%f\n%f", (-b + D) / (2*a), (-b - D) / (2 * a));

}
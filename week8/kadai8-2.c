#include <stdio.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Vector2d;

double GetLength(Vector2d *vec) {
    return sqrt(pow(vec->x, 2) + pow(vec->y, 2));
}

int main(void) {
    double x, y;
    double len;
    printf("Input 2D Vector: ");
    scanf("%lf %lf", &x, &y);
    Vector2d vec = {x,y};
    len = GetLength(&vec);
    printf("Length: %lf", len);
    return 0;
}
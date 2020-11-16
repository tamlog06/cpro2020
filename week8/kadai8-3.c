#include <stdio.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Vector2d;

double GetLength(Vector2d *vec) {
    return sqrt(pow(vec->x, 2) + pow(vec->y, 2));
}

void ScaleVector(Vector2d *vec, double s) {
    vec->x *= s;
    vec->y *= s;
}

int main(void) {
    double x, y;
    double s;
    double len;
    printf("Input 2D Vector: ");
    scanf("%lf %lf", &x, &y);
    printf("Input scale value: ");
    Vector2d vec = {x, y};
    scanf("%lf", &s);
    ScaleVector(&vec, s);
    printf("Result: %lf %lf\n", vec.x, vec.y);
    len = GetLength(&vec);
    printf("Length: %lf\n", len);
    return 0;
}
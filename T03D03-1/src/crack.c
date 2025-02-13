#include <stdio.h>
#define RADIUS 5.0

int main() {
    double x, y;
    double distance_squared;

    if (scanf("%lf %lf", &x, &y) != 2) {
        printf("n/a\n");
        return 1;
    }

    distance_squared = x * x + y * y;

    if (distance_squared <= RADIUS * RADIUS) {
        printf("GOTCHA\n");
    } else {
        printf("MISS\n");
    }

    return 0;
}
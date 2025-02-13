#include <math.h>
#include <stdio.h>

#define PI 3.14159265358979323846

int main() {
    double x, step;
    int i;

    step = 2 * PI / 41;

    x = -PI;
    for (i = 0; i < 42; i++) {
        double y1 = 1 / (1 + x * x);

        double y2 = -1;
        double temp = sqrt(1 + 4 * x * x) - x * x - 1;
        if (temp >= 0) {
            y2 = sqrt(temp);
        }

        double y3 = (x != 0) ? 1 / (x * x) : -1;

        printf("%.7f | %.7f | ", x, y1);
        if (y2 >= 0) {
            printf("%.7f", y2);
        } else {
            printf("-");
        }
        printf(" | %.7f\n", y3);

        x += step;
    }

    return 0;
}
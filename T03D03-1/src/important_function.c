#include <math.h>
#include <stdio.h>

double calculate_y(double x) {
    double y;

    y = 7e-3 * pow(x, 4) + ((22.8 * pow(x, 1.0 / 3) - 1e3) * x + 3) / (x * x / 2) - x * pow(10 + x, 2 / x) -
        1.01;

    return y;
}

int main() {
    double x, y;

    if (scanf("%lf", &x) != 1) {
        printf("n/a\n");
        return 1;
    }

    y = calculate_y(x);
    printf("%.1f\n", y);

    return 0;
}
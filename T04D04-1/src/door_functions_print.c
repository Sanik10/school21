#include <math.h>
#include <stdio.h>

#define PI 3.14159265358979323846

int main() {
    double x, step;
    int i, j;

    step = 2 * PI / 41;

    x = -PI;
    for (i = 0; i < 42; i++) {
        // Вычисляем значения функций
        double y1 = 1 / (1 + x * x);
        double y2 = (x >= -1 && x <= 1) ? sqrt(sqrt(1 + 4 * x * x) - x * x - 1) : -1;
        double y3 = (x != 0) ? 1 / (x * x) : -1;

        // Выводим значения в табличном виде
        printf("%.7f | %.7f | ", x, y1);
        if (y2 >= 0) {
            printf("%.7f", y2);
        } else {
            printf("-");
        }
        printf(" | %.7f\n", y3);

        // Отрисовка графиков
        for (j = 0; j < 21; j++) {
            // Верзьера Аньези (инвертируем ось Y)
            if (j == (int)(10.5 - y1 * 10)) {
                printf("*");
            } else {
                printf(" ");
            }

            // Лемниската Бернулли
            if (y2 >= 0 && j == (int)(10.5 - y2 * 10)) {
                printf(" *");
            } else {
                printf("  ");
            }

            // Квадратичная гипербола
            if (y3 >= 0 && j == (int)(10.5 - y3 * 10)) {
                printf(" *");
            } else {
                printf("  ");
            }
            printf("\n");
        }
        printf("----------------------------------------------------------------\n");

        x += step;
    }

    return 0;
}
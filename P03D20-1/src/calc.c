#include "calc.h"

#include <stdio.h>

#include "settings.h"

// Функция для перевода масштаба от (0 до 79) в (0 до 4π)
double scale_to_4pi(int value) { return (4 * M_PI * value) / (WIDTH - 1); }

// Функция для перевода масштаба от (0 до 4π) обратно в (0 до 79)
int scale_from_4pi(double value) { return (int)((value * (WIDTH - 1)) / (4 * M_PI)); }

int scale_to_i(double value) {
    double new = value + 1;
    new *= (HEIGHT - 1);
    new /= 2;
    return round(new);
}

void array_to_matrix(double *array, double **matrix) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            matrix[i][j] = (scale_to_i(array[i]) == i) ? 1 : 0;
        }
    }
    free(array);
}

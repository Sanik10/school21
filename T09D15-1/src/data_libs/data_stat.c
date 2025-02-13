#include "data_stat.h"

#include <math.h>

double max(double *data, int n) {
    double max = data[0];
    for (int i = 1; i < n; i++) {
        if (max < data[i]) {
            max = data[i];
        }
    }
    return max;
}

double min(double *data, int n) {
    double min = data[0];
    for (int i = 1; i < n; i++) {
        if (min > data[i]) {
            min = data[i];
        }
    }
    return min;
}

double mean(double *data, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += data[i];
    }
    return sum / n;
}

double variance(double *data, int n, double mean) {
    double sum_of_squares = 0;
    for (int i = 0; i < n; i++) {
        sum_of_squares += (data[i] - mean) * (data[i] - mean);
    }
    return sum_of_squares / n;
}
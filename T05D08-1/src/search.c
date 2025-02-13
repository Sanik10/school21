#include <math.h>
#include <stdio.h>
#define NMAX 30

int input(int *a, int *n);
double mean(int *a, int n);
double variance(int *a, int n);
int find_first_desired_number(int *a, int n, double mean_v, double variance_v);

int main() {
    int n, data[NMAX];
    if (input(data, &n) != 0) {
        printf("n/a\n");
        return 1;
    }

    double mean_v = mean(data, n);
    double variance_v = variance(data, n);

    int result = find_first_desired_number(data, n, mean_v, variance_v);

    printf("%d\n", result);

    return 0;
}

int input(int *a, int *n) {
    if (scanf("%d", n) != 1) {
        return 1;
    }
    if (*n > NMAX || *n <= 0) {
        return 1;
    }
    for (int i = 0; i < *n; i++) {
        if (scanf("%d", &a[i]) != 1) {
            return 1;
        }
    }
    char p = getchar();
    if (p != '\n') {
        return 1;
    }
    return 0;
}

double mean(int *a, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    return sum / n;
}

double variance(int *a, int n) {
    double mean_value = mean(a, n);
    double sum_sq_diff = 0.0;
    for (int i = 0; i < n; i++) {
        sum_sq_diff += (a[i] - mean_value) * (a[i] - mean_value);
    }
    return sum_sq_diff / n;
}

int find_first_desired_number(int *a, int n, double mean_v, double variance_v) {
    double max_allowed_value = mean_v + 3 * sqrt(variance_v);

    for (int i = 0; i < n; i++) {
        if (a[i] != 0 && a[i] % 2 == 0 && a[i] >= mean_v && a[i] <= max_allowed_value) {
            return a[i];
        }
    }
    return 0;
}
#include <math.h>
#include <stdio.h>
#define NMAX 100

int input(int *a, int *n);
void output(int *a, int n);
void output_result(int max_v, int min_v, double mean_v, double variance_v);
int max(int *a, int n);
int min(int *a, int n);
double mean(int *a, int n);
double variance(int *a, int n);

int main() {
    int n, data[NMAX];
    if (input(data, &n) != 0) {
        return 1;
    }
    output(data, n);

    int max_v = max(data, n);
    int min_v = min(data, n);
    double mean_v = mean(data, n);
    double variance_v = variance(data, n);

    output_result(max_v, min_v, mean_v, variance_v);

    return 0;
}

int input(int *a, int *n) {
    if (scanf("%d", n) != 1) {
        printf("n/a\n");
        return 1;
    }
    if (*n > NMAX || *n <= 0) {
        printf("n/a\n");
        return 1;
    }
    for (int i = 0; i < *n; i++) {
        if (scanf("%d", &a[i]) != 1) {
            printf("n/a\n");
            return 1;
        }
    }
    char p = getchar();
    if (p != '\n') {
        printf("n/a\n");
        return 1;
    }
    return 0;
}

void output(int *a, int n) {
    for (int i = 0; i < n; i++) {
        if (i == n - 1) {
            printf("%d\n", a[i]);
        } else {
            printf("%d ", a[i]);
        }
    }
}

void output_result(int max_v, int min_v, double mean_v, double variance_v) {
    printf("%d %d %.6lf %.6lf\n", max_v, min_v, mean_v, variance_v);
}

int max(int *a, int n) {
    int max_value = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] > max_value) {
            max_value = a[i];
        }
    }
    return max_value;
}

int min(int *a, int n) {
    int min_value = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] < min_value) {
            min_value = a[i];
        }
    }
    return min_value;
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
    return (double)(n * n - 1) / 12;
}
#include <stdio.h>
#include <stdlib.h>

#include "../data_libs/data_io.h"
#include "data_process.h"

int main() {
    int n;
    int flag = 0;

    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("ERROR");
        flag = 1;
    }

    double *data = (double *)malloc(n * sizeof(double));

    if (data == NULL && !flag) {
        printf("ERROR");
        flag = 1;
    }
    // Don`t forget to allocate memory !

    input(data, n);

    if (normalization(data, n) && !flag) {
        output(data, n);
    } else {
        printf("ERROR");
    }

    free(data);
    return flag;
}

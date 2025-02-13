#include <stdio.h>
#include <stdlib.h>

#include "../data_libs/data_io.h"
#include "decision.h"

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

    input(data, n);

    if (make_decision(data, n) && !flag) {
        printf("YES");
    } else {
        printf("NO");
    }
    return flag;
}

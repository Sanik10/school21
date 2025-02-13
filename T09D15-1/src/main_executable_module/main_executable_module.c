#include <stdio.h>
#include <stdlib.h>

#include "../data_module/data_process.h"
#include "../yet_another_decision_module/decision.h"

#ifdef USE_MACRO_IO
#include "../data_libs/data_io_macro.h"
#else
#include "../data_libs/data_io.h"
#endif

#define MAX_SIZE 100

int main() {
    int n;

    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("ERROR: Invalid input.\n");
        return 1;
    }

    if (n > MAX_SIZE) {
        printf("ERROR: Input exceeds maximum allowed size.\n");
        return 1;
    }

    double *data = (double *)malloc(n * sizeof(double));

    if (data == NULL) {
        printf("ERROR: Memory allocation failed.\n");
        return 1;
    }

    printf("LOAD DATA...\n");
#ifdef USE_MACRO_IO
    input_double(data, n);
    printf("RAW DATA:\n\t");
    output_double(data, n);
#else
    input(data, n);
    printf("RAW DATA:\n\t");
    output(data, n);
#endif

    printf("\nNORMALIZED DATA:\n\t");
    normalization(data, n);
#ifdef USE_MACRO_IO
    output_double(data, n);
#else
    output(data, n);
#endif

    printf("\nSORTED NORMALIZED DATA:\n\t");
    sort(data, n);
#ifdef USE_MACRO_IO
    output_double(data, n);
#else
    output(data, n);
#endif

    printf("\nFINAL DECISION:\n\t");
    if (make_decision(data, n)) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    free(data);
    return 0;
}
#ifndef DATA_IO_MACRO_H
#define DATA_IO_MACRO_H

#include <stdio.h>

#define DATA_IO_MACRO(TYPE, FORMAT_IN, FORMAT_OUT) \
    void input_##TYPE(TYPE *data, int n) {         \
        for (int i = 0; i < n; i++) {              \
            scanf(FORMAT_IN, &data[i]);            \
        }                                          \
    }                                              \
    void output_##TYPE(TYPE *data, int n) {        \
        for (int i = 0; i < n; i++) {              \
            printf(FORMAT_OUT, data[i]);           \
            if (i != n - 1) printf(" ");           \
        }                                          \
    }

DATA_IO_MACRO(int, "%d", "%d")
DATA_IO_MACRO(double, "%lf", "%.2f")
DATA_IO_MACRO(float, "%f", "%.2f")

#endif
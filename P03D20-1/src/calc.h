#ifndef CALC_H
#define CALC_H

#include "settings.h"

double scale_to_4pi(int value);
int scale_from_4pi(double value);
int scale_to_i(double value);
void array_to_matrix(double *array, double **matrix);

#endif

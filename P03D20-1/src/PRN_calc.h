#ifndef PRN_CALC_H
#define PRN_CALC_H

#include "settings.h"

double calculate_postfix(list_node *postfix, double x);
double *calculate_array(list_node *postfix);

#endif
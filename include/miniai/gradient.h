#ifndef MINIAI_GRADIENT_H
#define MINIAI_GRADIENT_H

#include <stddef.h>
#include "miniai/objective.h"

enum { MINIAI_GRADIENT_OK = 0, MINIAI_GRADIENT_INVALID_ARGUMENT = 1,
       MINIAI_GRADIENT_NONFINITE_OBJECTIVE = 2, MINIAI_GRADIENT_NO_MEMORY = 3 };

int miniai_gradient_forward(miniai_objective_function f, const double x[], size_t n,
    double h, void *context, double gradient[]);
int miniai_gradient_central(miniai_objective_function f, const double x[], size_t n,
    double h, void *context, double gradient[]);
int miniai_gradient_forward_safe(miniai_objective_function f, const double x[],
    size_t n, double h, void *context, double gradient[]);

#endif
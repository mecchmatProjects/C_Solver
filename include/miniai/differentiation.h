#ifndef MINIAI_DIFFERENTIATION_H
#define MINIAI_DIFFERENTIATION_H

#include <stddef.h>

typedef double (*miniai_scalar_function)(double x);

double miniai_derivative_forward(miniai_scalar_function f, double x, double h);
double miniai_derivative_backward(miniai_scalar_function f, double x, double h);
double miniai_derivative_central(miniai_scalar_function f, double x, double h);
int miniai_is_valid_step(double h);

#endif // MINIAI_DIFFERENTIATION_H
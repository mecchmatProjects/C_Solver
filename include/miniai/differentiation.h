#ifndef MINIAI_DIFFERENTIATION_H
#define MINIAI_DIFFERENTIATION_H

#include <stddef.h>
#include "miniai/objective.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef double (*miniai_scalar_function)(double x);
typedef double (*miniai_scalar_function_with_context)(double x, void *user_data);

int miniai_is_valid_step(double h);

double miniai_differentiate_scalar_checked(
    miniai_scalar_function_with_context f,
    double x,
    double h,
    void *user_data
);

int miniai_gradient_checked(
    miniai_objective_function f,
    const double *x,
    size_t n,
    double h,
    double *grad_out,
    void *user_data
);

double miniai_derivative_forward(miniai_scalar_function f, double x, double h);
double miniai_derivative_backward(miniai_scalar_function f, double x, double h);
double miniai_derivative_central(miniai_scalar_function f, double x, double h);

#ifdef __cplusplus
}
#endif

#endif /* MINIAI_DIFFERENTIATION_H */

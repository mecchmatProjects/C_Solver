#ifndef MINIAI_DIFFERENTIATION_H
#define MINIAI_DIFFERENTIATION_H

#include <stddef.h>
#include "miniai/objective.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Типи callback-функцій для скалярної та багатовимірної цільових функцій */
typedef double (*miniai_scalar_function)(double x);
typedef double (*miniai_scalar_function_with_context)(double x, void *user_data);

/* Перевіряє, чи є крок h скінченним та строго додатним числом (повертає 1 або 0) */
int miniai_is_valid_step(double h);

/* Обчислює центральну похідну з перевіркою аргументів; у разі помилки повертає NAN */
double miniai_differentiate_scalar_checked(
    miniai_scalar_function_with_context f,
    double x,
    double h,
    void *user_data
);

/* Перевіряє контракти параметрів для градієнта; у разі помилки повертає ненульовий код */
int miniai_gradient_checked(
    miniai_objective_function f,
    const double *x,
    size_t n,
    double h,
    double *grad_out,
    void *user_data
);

/* Одновимірні похідні для функцій без додаткового контексту. */
double miniai_derivative_backward(miniai_scalar_function f, double x, double h);
double miniai_derivative_central(miniai_scalar_function f, double x, double h);

#ifdef __cplusplus
}
#endif

#endif /* MINIAI_DIFFERENTIATION_H */

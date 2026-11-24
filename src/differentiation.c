//
// Created by Katya on 24.11.2026.
//
#include "miniai/differentiation.h"

#include <math.h>
#include <stddef.h>
double miniai_derivative_backward(miniai_scalar_function f,
                                  double x, double h) {
    if (f == NULL || !isfinite(x) || !isfinite(h) || h <= 0.0) {
        return NAN;
    }

    double previous_x = x - h;

    if (!isfinite(previous_x)) {
        return NAN;
    }

    double value = f(x);
    double previous_value = f(previous_x);

    if (!isfinite(value) || !isfinite(previous_value)) {
        return NAN;
    }

    double derivative = (value - previous_value) / h;

    if (!isfinite(derivative)) {
        return NAN;
    }

    return derivative;
}
#include "miniai/differentiation.h"

#include <math.h>

double miniai_derivative_central(miniai_scalar_function f, double x, double h) {
    double f_plus;
    double f_minus;
    double result;

    if (f == NULL || !isfinite(h) || h <= 0.0) {
        return NAN;
    }
    if (!isfinite(x + h) || !isfinite(x - h)) {
        return NAN;
    }

    f_plus = f(x + h);
    f_minus = f(x - h);
    if (!isfinite(f_plus) || !isfinite(f_minus)) {
        return NAN;
    }

    result = (f_plus - f_minus) / 2.0 / h;
    return isfinite(result) ? result : NAN;
}

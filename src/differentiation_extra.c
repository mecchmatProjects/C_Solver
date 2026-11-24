#include "miniai/differentiation_extra.h"

#include <math.h>

static double central_diff_local(miniai_scalar_function f, double x, double h) {
    double two_h = 2.0 * h;
    double x_plus = x + h;
    double x_minus = x - h;

    if (!isfinite(two_h) || two_h <= 0.0 || !isfinite(x_plus) || !isfinite(x_minus)) {
        return NAN;
    }

    double f_plus = f(x_plus);
    double f_minus = f(x_minus);

    if (!isfinite(f_plus) || !isfinite(f_minus)) {
        return NAN;
    }

    double result = (f_plus - f_minus) / two_h;
    return isfinite(result) ? result : NAN;
}

double miniai_derivative_richardson(miniai_scalar_function f, double x, double h) {
    if (f == NULL || !isfinite(x) || !isfinite(h) || h <= 0.0) {
        return NAN;
    }

    double half_h = h * 0.5;
    if (!isfinite(half_h) || half_h <= 0.0) {
        return NAN;
    }

    double d_h = central_diff_local(f, x, h);
    double d_half = central_diff_local(f, x, half_h);

    if (!isfinite(d_h) || !isfinite(d_half)) {
        return NAN;
    }

    double result = (4.0 * d_half - d_h) / 3.0;
    return isfinite(result) ? result : NAN;
}
#include "miniai/differentiation_extra.h"

#include <math.h>

double miniai_derivative_richardson(miniai_scalar_function f, double x, double h) {
    if (!miniai_is_valid_step(h)) {
        return NAN;
    }
    double half_h = h * 0.5;
    if (!miniai_is_valid_step(half_h)) {
        return NAN;
    }

    double dc_h = miniai_derivative_central(f, x, h);
    double dc_h2 = miniai_derivative_central(f, x, half_h);
    if (!isfinite(dc_h) || !isfinite(dc_h2)) {
        return NAN;
    }

    double res = (4.0 * dc_h2 - dc_h) / 3.0;
    return isfinite(res) ? res : NAN;
}
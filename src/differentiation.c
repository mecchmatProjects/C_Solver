#include "miniai/differentiation.h"

#include <math.h>
#include <stddef.h>

int miniai_is_valid_step(double h) {
    return isfinite(h) && h > 0.0 ? 1 : 0;
}

static int miniai_valid_scalar_inputs(miniai_scalar_function f, double x, double h) {
    if (f == NULL || !isfinite(x) || !miniai_is_valid_step(h)) {
        return 0;
    }
    return isfinite(x - h) && isfinite(x + h) ? 1 : 0;
}

double miniai_derivative_forward(miniai_scalar_function f, double x, double h) {
    if (!miniai_valid_scalar_inputs(f, x, h)) {
        return NAN;
    }
    double fx = f(x);
    double fxp = f(x + h);
    if (!isfinite(fx) || !isfinite(fxp)) {
        return NAN;
    }
    double res = (fxp - fx) / h;
    return isfinite(res) ? res : NAN;
}

double miniai_derivative_backward(miniai_scalar_function f, double x, double h) {
    if (!miniai_valid_scalar_inputs(f, x, h)) {
        return NAN;
    }
    double fx = f(x);
    double fxm = f(x - h);
    if (!isfinite(fx) || !isfinite(fxm)) {
        return NAN;
    }
    double res = (fx - fxm) / h;
    return isfinite(res) ? res : NAN;
}

double miniai_derivative_central(miniai_scalar_function f, double x, double h) {
    if (!miniai_valid_scalar_inputs(f, x, h)) {
        return NAN;
    }
    double fxp = f(x + h);
    double fxm = f(x - h);
    if (!isfinite(fxp) || !isfinite(fxm)) {
        return NAN;
    }
    double res = (fxp - fxm) / (2.0 * h);
    return isfinite(res) ? res : NAN;
}
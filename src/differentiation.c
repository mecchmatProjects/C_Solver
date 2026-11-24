#include "miniai/differentiation.h"

#include <math.h>

double miniai_derivative_forward(miniai_scalar_function f, double x, double h) {
    if (f == NULL || !isfinite(x) || !isfinite(h) || h <= 0.0) {
        return NAN;
    }

    double xh = x + h;
    if (!isfinite(xh)) {
        return NAN;
    }

    double fxh = f(xh);
    double fx = f(x);

    if (!isfinite(fxh) || !isfinite(fx)) {
        return NAN;
    }

    double result = (fxh - fx) / h;
    return isfinite(result) ? result : NAN;
}

#include "miniai/differentiation_extra.h"

#include <math.h>

double miniai_second_derivative_central(miniai_scalar_function f, double x, double h) {
    if (f == NULL || !isfinite(x) || !isfinite(h) || h <= 0.0) {
        return NAN;
    }

    double x_plus = x + h;
    double x_minus = x - h;
    double h_sq = h * h;

    if (!isfinite(x_plus) || !isfinite(x_minus) || !isfinite(h_sq) || h_sq <= 0.0) {
        return NAN;
    }

    double f_plus = f(x_plus);
    double f_mid = f(x);
    double f_minus = f(x_minus);

    if (!isfinite(f_plus) || !isfinite(f_mid) || !isfinite(f_minus)) {
        return NAN;
    }

    double two_mid = 2.0 * f_mid;
    if (!isfinite(two_mid)) {
        return NAN;
    }

    double diff = f_plus - two_mid;
    if (!isfinite(diff)) {
        return NAN;
    }

    double numerator = diff + f_minus;
    if (!isfinite(numerator)) {
        return NAN;
    }

    double result = numerator / h_sq;
    return isfinite(result) ? result : NAN;
}
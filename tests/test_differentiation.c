#include <float.h>
#include <math.h>
#include <stdio.h>

#include "miniai/differentiation.h"

static int failures = 0;

static double square(double x) {
    return x * x;
}

static double exponent(double x) {
    return exp(x);
}

static double sine(double x) {
    return sin(x);
}

static double bad(double x) {
    (void)x;
    return NAN;
}

static int near(double actual, double expected) {
    return isfinite(actual) && isfinite(expected) &&
           fabs(actual - expected) <=
               1e-8 + 1e-9 * fmax(fabs(actual), fabs(expected));
}

static void check(int condition, const char *message) {
    if (!condition) {
        fprintf(stderr, "FAIL: %s\n", message);
        ++failures;
    }
}

int main(void) {
    double error_h;
    double error_half;

    check(near(miniai_derivative_central(square, 2.0, 1e-4), 4.0), "x^2 at 2");
    check(near(miniai_derivative_central(sine, 0.0, 1e-4), 1.0), "sin at 0");
    check(near(miniai_derivative_central(exponent, 0.0, 1e-4), 1.0), "exp at 0");

    error_h = fabs(miniai_derivative_central(exponent, 0.0, 1e-2) - 1.0);
    error_half = fabs(miniai_derivative_central(exponent, 0.0, 5e-3) - 1.0);
    check(error_h / error_half > 3.5 && error_h / error_half < 4.5,
          "order O(h^2)");

    check(isnan(miniai_derivative_central(square, 2.0, 0.0)), "h = 0");
    check(isnan(miniai_derivative_central(square, 2.0, -1e-4)), "h < 0");
    check(isnan(miniai_derivative_central(square, 2.0, NAN)), "h = NAN");
    check(isnan(miniai_derivative_central(NULL, 2.0, 1e-4)), "f = NULL");
    check(isnan(miniai_derivative_central(square, DBL_MAX, DBL_MAX)),
          "x + h overflow");
    check(isnan(miniai_derivative_central(bad, 0.0, 1e-4)), "f returns NAN");

    if (failures != 0) {
        fprintf(stderr, "%d central difference checks failed\n", failures);
        return 1;
    }
    printf("10 central difference checks passed\n");
    return 0;
}

//
// Created by Katya on 24.11.2026.
//
#include <float.h>
#include <math.h>
#include <stdio.h>

#include "miniai/differentiation.h"

static int failures = 0;

static double square(double x) {
    return x * x;
}

static int near(double actual, double expected, double tolerance) {
    return isfinite(actual) && isfinite(expected) &&
           fabs(actual - expected) <=
               tolerance + 1e-9 * fmax(fabs(actual), fabs(expected));
}

static void check(int condition, const char *name) {
    if (condition) {
        printf("PASS: %s\n", name);
    } else {
        printf("FAIL: %s\n", name);
        failures++;
    }
}

int main(void) {
    double result = miniai_derivative_backward(square, 2.0, 0.001);
    check(near(result, 4.0, 0.0011), "square at x=2");
    check(near(result, 3.999, 1e-12), "backward formula gives 4-h");

    result = miniai_derivative_backward(square, -2.0, 0.001);
    check(near(result, -4.0, 0.0011), "negative derivative");

    result = miniai_derivative_backward(exp, 0.0, 0.0001);
    check(near(result, 1.0, 0.00006), "exp at x=0");

    double h = 0.1;
    double backward = miniai_derivative_backward(square, 2.0, h);
    double forward = (square(2.0 + h) - square(2.0)) / h;

    check(near(backward, 3.9, 1e-12), "backward comparison");
    check(near(forward, 4.1, 1e-12), "forward comparison");

    printf("Exact: 4, backward: %.6f, forward: %.6f\n",
           backward, forward);

    double smaller = miniai_derivative_backward(square, 2.0, h / 2.0);
    double error = fabs(backward - 4.0);
    double smaller_error = fabs(smaller - 4.0);

    check(near(smaller_error, error / 2.0, 1e-12),
          "halving h halves the error");

    check(isnan(miniai_derivative_backward(NULL, 2.0, 0.1)),
          "NULL function");
    check(isnan(miniai_derivative_backward(square, 2.0, 0.0)),
          "zero step");
    check(isnan(miniai_derivative_backward(square, 2.0, -0.1)),
          "negative step");
    check(isnan(miniai_derivative_backward(square, 2.0, NAN)),
          "NaN step");
    check(isnan(miniai_derivative_backward(square, 2.0, INFINITY)),
          "infinite step");
    check(isnan(miniai_derivative_backward(square, NAN, 0.1)),
          "NaN x");
    check(isnan(miniai_derivative_backward(square, INFINITY, 0.1)),
          "infinite x");
    check(isnan(miniai_derivative_backward(square, -DBL_MAX, DBL_MAX)),
          "x-h overflow");
    check(isnan(miniai_derivative_backward(exp, 1000.0, 0.1)),
          "infinite function value");
    check(isnan(miniai_derivative_backward(sqrt, 0.0, 0.1)),
          "NaN function value at x-h");

    printf("Failures: %d\n", failures);
    return failures != 0;
}

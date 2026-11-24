#include "miniai/differentiation.h"
#include "test_functions.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>

#define TEST_TWO_PI 6.28318530717958647692

static int near_val(double actual, double expected, double abs_tol, double rel_tol) {
    return isfinite(actual) && isfinite(expected) &&
        fabs(actual - expected) <= abs_tol + rel_tol * fmax(fabs(actual), fabs(expected));
}

static void test_a1_forward(void) {
    assert(near_val(miniai_derivative_forward(test_poly_x2, 2.0, 1e-5), 4.0, 1e-4, 1e-4));
    assert(near_val(miniai_derivative_forward(test_sin, 0.0, 1e-5), 1.0, 1e-4, 1e-4));
}

static void test_a2_backward(void) {
    double fwd = miniai_derivative_forward(test_poly_x2, 2.0, 1e-3);
    double bwd = miniai_derivative_backward(test_poly_x2, 2.0, 1e-3);
    assert(near_val(bwd, 4.0, 2e-3, 1e-3));
    assert(fwd > 4.0 && bwd < 4.0);
    assert(near_val(miniai_derivative_backward(test_exp, 0.0, 1e-5), 1.0, 1e-4, 1e-4));
}

static void test_a3_central_and_order(void) {
    assert(near_val(miniai_derivative_central(test_poly_x2, 2.0, 1e-4), 4.0, 1e-9, 1e-9));
    assert(near_val(miniai_derivative_central(test_sin, 0.0, 1e-4), 1.0, 1e-7, 1e-7));
    assert(near_val(miniai_derivative_central(test_exp, 0.0, 1e-4), 1.0, 1e-7, 1e-7));

    double e1 = fabs(miniai_derivative_central(test_exp, 0.0, 1e-2) - 1.0);
    double e2 = fabs(miniai_derivative_central(test_exp, 0.0, 5e-3) - 1.0);
    double ratio = e1 / e2;
    assert(ratio > 3.5 && ratio < 4.5); /* O(h^2): halving h reduces error ~4x */
}

static void test_a5_fixtures(void) {
    const double pts[] = { -1.0, 0.0, 1.0 };
    for (size_t i = 0; i < 3; ++i) {
        double x = pts[i];
        assert(near_val(miniai_derivative_central(test_poly_x2, x, 1e-4), test_poly_x2_deriv(x), 1e-8, 1e-8));
        assert(near_val(miniai_derivative_central(test_sin, x, 1e-4), test_sin_deriv(x), 1e-7, 1e-7));
        assert(near_val(miniai_derivative_central(test_exp, x, 1e-4), test_exp_deriv(x), 1e-7, 1e-7));
    }
    assert(isinf(test_exp(1000.0)));
    assert(near_val(test_sin(0.5), test_sin(0.5 + TEST_TWO_PI), 1e-12, 1e-12));
}

int main(void) {
    test_a1_forward();
    test_a2_backward();
    test_a3_central_and_order();
    test_a5_fixtures();
    printf("All A1-A3, A5 differentiation tests passed!\n");
    return 0;
}
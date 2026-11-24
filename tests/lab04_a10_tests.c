#define MINIAI_DERIVATIVE_DEMO_NO_MAIN
#include "../examples/derivative_demo.c"

#include <assert.h>
#include <math.h>
#include <stdio.h>

static int near_val(double actual, double expected, double abs_tol, double rel_tol) {
    return isfinite(actual) && isfinite(expected) &&
        fabs(actual - expected) <= abs_tol + rel_tol * fmax(fabs(actual), fabs(expected));
}

static double bad_nan_fn(double x) {
    (void)x;
    return NAN;
}

static void test_known_derivatives(void) {
    assert(near_val(demo_derivative_central(fn_square, 2.0, 1e-4), 4.0, 1e-9, 1e-9));
    assert(near_val(demo_derivative_central(fn_sin, 0.0, 1e-4), 1.0, 1e-7, 1e-7));
    assert(near_val(demo_derivative_central(fn_exp, 0.0, 1e-4), 1.0, 1e-7, 1e-7));
}

static void test_central_more_accurate_than_forward(void) {
    double h = 1e-2;
    double err_fwd = fabs(demo_derivative_forward(fn_exp, 0.0, h) - 1.0);
    double err_cen = fabs(demo_derivative_central(fn_exp, 0.0, h) - 1.0);
    assert(err_cen < err_fwd);
}

static void test_invalid_inputs_return_nan(void) {
    assert(isnan(demo_derivative_forward(NULL, 1.0, 1e-4)));
    assert(isnan(demo_derivative_backward(fn_square, 1.0, 0.0)));
    assert(isnan(demo_derivative_central(fn_square, 1.0, -1e-3)));
    assert(isnan(demo_derivative_central(fn_square, 1.0, NAN)));
    assert(isnan(demo_derivative_central(fn_square, 1.0, INFINITY)));
}

static void test_nonfinite_callback_returns_nan(void) {
    assert(isnan(demo_derivative_forward(bad_nan_fn, 1.0, 1e-4)));
    assert(isnan(demo_derivative_backward(bad_nan_fn, 1.0, 1e-4)));
    assert(isnan(demo_derivative_central(bad_nan_fn, 1.0, 1e-4)));
}

static void test_run_demo_returns_zero(void) {
    assert(run_derivative_demo() == 0);
}

int main(void) {
    test_known_derivatives();
    test_central_more_accurate_than_forward();
    test_invalid_inputs_return_nan();
    test_nonfinite_callback_returns_nan();
    test_run_demo_returns_zero();
    printf("All Lab 4 A10 tests passed!\n");
    return 0;
}
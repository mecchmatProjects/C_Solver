#include "miniai/differentiation_extra.h"

#include <assert.h>
#include <float.h>
#include <math.h>
#include <stdio.h>

static int near(double actual, double expected) {
    return isfinite(actual) && isfinite(expected) &&
           fabs(actual - expected) <= 1e-12 + 1e-9 * fmax(fabs(actual), fabs(expected));
}

static double ref_central(miniai_scalar_function f, double x, double h) {
    return (f(x + h) - f(x - h)) / (2.0 * h);
}

static double fn_x2(double x) {
    return x * x;
}

static double fn_x4(double x) {
    double x2 = x * x;
    return x2 * x2;
}

static double fn_exp(double x) {
    return exp(x);
}

static double fn_nan(double x) {
    (void)x;
    return NAN;
}

static double fn_inf(double x) {
    (void)x;
    return INFINITY;
}

static double fn_jump(double x) {
    return x > 0.0 ? 1.0 : -1.0;
}

int main(void) {
    {
        double dr_x2 = miniai_derivative_richardson(fn_x2, 2.0, 1e-2);
        assert(near(dr_x2, 4.0));

        double h = 0.1;
        double err_c = fabs(ref_central(fn_x4, 2.0, h) - 32.0);
        double err_r = fabs(miniai_derivative_richardson(fn_x4, 2.0, h) - 32.0);
        assert(near(miniai_derivative_richardson(fn_x4, 2.0, h), 32.0));
        assert(err_r < err_c);
    }

    {
        double exact = exp(1.0);
        double h = 0.1;
        double err_c = fabs(ref_central(fn_exp, 1.0, h) - exact);
        double err_r = fabs(miniai_derivative_richardson(fn_exp, 1.0, h) - exact);
        assert(err_r < err_c);
        assert(near(miniai_derivative_richardson(fn_exp, 1.0, 1e-2), exact));
    }

    {
        assert(isnan(miniai_derivative_richardson(NULL, 1.0, 1e-3)));
        assert(isnan(miniai_derivative_richardson(fn_x2, 1.0, 0.0)));
        assert(isnan(miniai_derivative_richardson(fn_x2, 1.0, -1e-3)));
        assert(isnan(miniai_derivative_richardson(fn_x2, 1.0, NAN)));
        assert(isnan(miniai_derivative_richardson(fn_x2, 1.0, INFINITY)));
        assert(isnan(miniai_derivative_richardson(fn_x2, NAN, 1e-3)));
        assert(isnan(miniai_derivative_richardson(fn_x2, INFINITY, 1e-3)));
    }

    {
        assert(isnan(miniai_derivative_richardson(fn_x2, 1.0, DBL_TRUE_MIN)));
        assert(isnan(miniai_derivative_richardson(fn_x2, DBL_MAX, 1.0)));
        assert(isnan(miniai_derivative_richardson(fn_x2, 1.0, DBL_MAX)));
        assert(isnan(miniai_derivative_richardson(fn_nan, 1.0, 1e-3)));
        assert(isnan(miniai_derivative_richardson(fn_inf, 1.0, 1e-3)));
    }

    {
        assert(isnan(miniai_derivative_richardson(fn_jump, 0.0, 1e-308)));
    }

    {
        double exact = exp(1.0);
        double steps[] = {1e-1, 1e-2, 1e-3, 1e-6, 1e-10, 1e-13};
        size_t count = sizeof(steps) / sizeof(steps[0]);

        printf("%-10s %-18s %-18s\n", "h", "central_err", "richardson_err");
        for (size_t i = 0; i < count; ++i) {
            double h = steps[i];
            double ec = fabs(ref_central(fn_exp, 1.0, h) - exact);
            double er = fabs(miniai_derivative_richardson(fn_exp, 1.0, h) - exact);
            printf("%-10.1e %-18.3e %-18.3e\n", h, ec, er);
        }

        double err_good = fabs(miniai_derivative_richardson(fn_exp, 1.0, 1e-3) - exact);
        double err_tiny = fabs(miniai_derivative_richardson(fn_exp, 1.0, 1e-13) - exact);
        assert(isfinite(err_good) && isfinite(err_tiny));
        assert(err_tiny > err_good * 100.0);
    }

    printf("lab04_a8_tests: PASSED\n");
    return 0;
}
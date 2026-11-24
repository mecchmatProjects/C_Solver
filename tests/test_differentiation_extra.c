#include "miniai/differentiation_extra.h"

#include <assert.h>
#include <float.h>
#include <math.h>
#include <stdio.h>

static int near_tol(double actual, double expected, double abs_tol, double rel_tol) {
    return isfinite(actual) && isfinite(expected) &&
           fabs(actual - expected) <= abs_tol + rel_tol * fmax(fabs(actual), fabs(expected));
}

static int near(double actual, double expected) {
    return near_tol(actual, expected, 1e-12, 1e-9);
}

static double fn_x2(double x) {
    return x * x;
}

static double fn_x3(double x) {
    return x * x * x;
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

static double fn_huge(double x) {
    (void)x;
    return DBL_MAX;
}

static double fn_step(double x) {
    return x > 0.0 ? 10.0 : 0.0;
}

int main(void) {
    {
        assert(near(miniai_second_derivative_central(fn_x2, 0.0, 1e-2), 2.0));
        assert(near(miniai_second_derivative_central(fn_x2, 2.0, 1e-2), 2.0));
    }

    {
        assert(near(miniai_second_derivative_central(fn_x3, 1.0, 1e-2), 6.0));
    }

    {
        double points[] = {-1.0, 0.0, 1.0, 2.0};
        size_t count = sizeof(points) / sizeof(points[0]);
        for (size_t i = 0; i < count; ++i) {
            double x = points[i];
            double approx = miniai_second_derivative_central(fn_exp, x, 1e-4);
            assert(near_tol(approx, exp(x), 1e-6, 1e-6));
        }
    }

    {
        assert(isnan(miniai_second_derivative_central(NULL, 1.0, 1e-3)));
        assert(isnan(miniai_second_derivative_central(fn_x2, 1.0, 0.0)));
        assert(isnan(miniai_second_derivative_central(fn_x2, 1.0, -1e-3)));
        assert(isnan(miniai_second_derivative_central(fn_x2, 1.0, NAN)));
        assert(isnan(miniai_second_derivative_central(fn_x2, 1.0, INFINITY)));
        assert(isnan(miniai_second_derivative_central(fn_x2, NAN, 1e-3)));
        assert(isnan(miniai_second_derivative_central(fn_x2, INFINITY, 1e-3)));
    }

    {
        assert(isnan(miniai_second_derivative_central(fn_x2, DBL_MAX, 1.0)));
        assert(isnan(miniai_second_derivative_central(fn_x2, -DBL_MAX, 1.0)));
        assert(isnan(miniai_second_derivative_central(fn_x2, 1.0, 1e200)));
        assert(isnan(miniai_second_derivative_central(fn_x2, 1.0, 1e-200)));
        assert(isnan(miniai_second_derivative_central(fn_nan, 1.0, 1e-3)));
        assert(isnan(miniai_second_derivative_central(fn_inf, 1.0, 1e-3)));
        assert(isnan(miniai_second_derivative_central(fn_huge, 1.0, 1e-3)));
        assert(isnan(miniai_second_derivative_central(fn_step, 0.0, 1e-154)));
    }

    {
        double exact = exp(1.0);
        double steps[] = {1e-1, 1e-2, 1e-3, 1e-4, 1e-6, 1e-8};
        size_t count = sizeof(steps) / sizeof(steps[0]);

        printf("%-10s %-18s %-18s\n", "h", "approx", "abs_error");
        for (size_t i = 0; i < count; ++i) {
            double h = steps[i];
            double approx = miniai_second_derivative_central(fn_exp, 1.0, h);
            double err = fabs(approx - exact);
            printf("%-10.1e %-18.10f %-18.3e\n", h, approx, err);
        }

        double err_1e1 = fabs(miniai_second_derivative_central(fn_exp, 1.0, 1e-1) - exact);
        double err_1e2 = fabs(miniai_second_derivative_central(fn_exp, 1.0, 1e-2) - exact);
        double err_opt = fabs(miniai_second_derivative_central(fn_exp, 1.0, 1e-4) - exact);
        double err_tiny = fabs(miniai_second_derivative_central(fn_exp, 1.0, 1e-8) - exact);

        assert(isfinite(err_1e1) && isfinite(err_1e2) && isfinite(err_opt) && isfinite(err_tiny));
        assert(err_1e2 < err_1e1 / 50.0);
        assert(err_tiny > err_opt * 100.0);
    }

    printf("lab04_b11_tests: PASSED\n");
    return 0;
}
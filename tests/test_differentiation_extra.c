#include "miniai/differentiation_extra.h"
#include "test_functions.h"

#include <assert.h>
#include <float.h>
#include <math.h>
#include <stdio.h>

static double bad_nan_fn(double x) {
    (void)x;
    return NAN;
}

int main(void) {
    double h = 1e-1;
    double err_central = fabs(miniai_derivative_central(test_exp, 0.0, h) - 1.0);
    double err_rich = fabs(miniai_derivative_richardson(test_exp, 0.0, h) - 1.0);
    assert(err_rich < err_central);
    assert(err_rich < 1e-5);

    double err_x3 = fabs(miniai_derivative_richardson(test_poly_x3, 2.0, 1e-2) - 12.0);
    assert(err_x3 < 1e-9);

    assert(isnan(miniai_derivative_richardson(NULL, 0.0, 1e-2)));
    assert(isnan(miniai_derivative_richardson(test_exp, 0.0, 0.0)));
    assert(isnan(miniai_derivative_richardson(test_exp, 0.0, -1e-2)));
    assert(isnan(miniai_derivative_richardson(bad_nan_fn, 0.0, 1e-2)));
    assert(isnan(miniai_derivative_richardson(test_exp, 0.0, DBL_TRUE_MIN)));

    printf("All A8 Richardson extrapolation tests passed!\n");
    return 0;
}
#include "miniai/differentiation.h"
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
    assert(miniai_is_valid_step(1e-5) == 1);
    assert(miniai_is_valid_step(DBL_MIN) == 1);
    assert(miniai_is_valid_step(DBL_MAX) == 1);

    assert(miniai_is_valid_step(0.0) == 0);
    assert(miniai_is_valid_step(-1e-3) == 0);
    assert(miniai_is_valid_step(NAN) == 0);
    assert(miniai_is_valid_step(INFINITY) == 0);
    assert(miniai_is_valid_step(-INFINITY) == 0);

    assert(isnan(miniai_derivative_forward(NULL, 1.0, 1e-4)));
    assert(isnan(miniai_derivative_backward(test_poly_x2, 1.0, 0.0)));
    assert(isnan(miniai_derivative_central(test_poly_x2, 1.0, -1.0)));
    assert(isnan(miniai_derivative_central(bad_nan_fn, 1.0, 1e-4)));

    /* x +/- h overflow */
    assert(isnan(miniai_derivative_forward(test_poly_x2, DBL_MAX, DBL_MAX)));
    assert(isnan(miniai_derivative_backward(test_poly_x2, -DBL_MAX, DBL_MAX)));

    printf("All A4 error & step validation tests passed!\n");
    return 0;
}
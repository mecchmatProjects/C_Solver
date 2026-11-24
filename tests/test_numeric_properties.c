#include "miniai/differentiation.h"
#include "test_functions.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>

static double ref_central_signed(miniai_scalar_function f, double x, double h) {
    return (f(x + h) - f(x - h)) / (2.0 * h);
}

int run_differentiation_tests(void) {
    /* 1. Symmetry of central difference: D_c(x, h) == D_c(x, -h) */
    double pos = ref_central_signed(test_exp, 0.5, 1e-3);
    double neg = ref_central_signed(test_exp, 0.5, -1e-3);
    assert(fabs(pos - neg) <= 1e-12);

    /* Public API still rejects h <= 0 */
    assert(isnan(miniai_derivative_central(test_exp, 0.5, -1e-3)));

    /* 2. Central more accurate than forward on smooth functions */
    double h = 1e-2;
    double fwd_err = fabs(miniai_derivative_forward(test_sin, 0.5, h) - test_sin_deriv(0.5));
    double cen_err = fabs(miniai_derivative_central(test_sin, 0.5, h) - test_sin_deriv(0.5));
    assert(cen_err < fwd_err);

    /* 3. Forward O(h) scaling: halving h halves error roughly 2x */
    double f1 = fabs(miniai_derivative_forward(test_exp, 0.0, 1e-2) - 1.0);
    double f2 = fabs(miniai_derivative_forward(test_exp, 0.0, 5e-3) - 1.0);
    double ratio = f1 / f2;
    assert(ratio > 1.8 && ratio < 2.2);

    return 0;
}

int main(void) {
    assert(run_differentiation_tests() == 0);
    printf("All A9 numeric property tests passed!\n");
    return 0;
}
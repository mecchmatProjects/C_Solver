#include <math.h>
#include <stdio.h>
#include "miniai/ml/activation/sinc.h"

#define DEFAULT_ABS_TOL 1e-12
#define DEFAULT_REL_TOL 1e-9
#define STRICT_ZERO_TOL 1e-16

static int almost_equal(double a, double b, double abs_tol, double rel_tol) {
    if (!isfinite(a) || !isfinite(b)) {
        return 0;
    }
    return fabs(a - b) <= abs_tol + rel_tol * fmax(fabs(a), fabs(b));
}

int main(void) {
    int failures = 0;
    Activation sinc;
    double y_pos = 0.0, y_neg = 0.0;
    double dy_pos = 0.0, dy_neg = 0.0;

    if (activation_sinc_init(NULL) != ACTIVATION_STATUS_INVALID_ARGUMENT) {
        fprintf(stderr, "FAIL: activation_sinc_init(NULL) must return INVALID_ARGUMENT\n");
        failures++;
    }
    if (activation_sinc_init(&sinc) != ACTIVATION_STATUS_OK) {
        fprintf(stderr, "FAIL: activation_sinc_init(&sinc) failed\n");
        return 1;
    }
    if (activation_value(&sinc, 0.0, NULL) != ACTIVATION_STATUS_INVALID_ARGUMENT ||
        activation_derivative(&sinc, 0.0, NULL) != ACTIVATION_STATUS_INVALID_ARGUMENT) {
        fprintf(stderr, "FAIL: NULL result pointer must return INVALID_ARGUMENT\n");
        failures++;
    }

    /* x = 0 */
    if (activation_value(&sinc, 0.0, &y_pos) != ACTIVATION_STATUS_OK ||
        !almost_equal(y_pos, 1.0, DEFAULT_ABS_TOL, DEFAULT_REL_TOL)) {
        failures++;
    }
    if (activation_derivative(&sinc, 0.0, &dy_pos) != ACTIVATION_STATUS_OK ||
        !almost_equal(dy_pos, 0.0, STRICT_ZERO_TOL, 0.0)) {
        failures++;
    }

    /* x = +-1 */
    double expected_val_1 = sin(1.0);
    if (activation_value(&sinc, 1.0, &y_pos) != ACTIVATION_STATUS_OK ||
        activation_value(&sinc, -1.0, &y_neg) != ACTIVATION_STATUS_OK ||
        !almost_equal(y_pos, expected_val_1, DEFAULT_ABS_TOL, DEFAULT_REL_TOL) ||
        !almost_equal(y_neg, expected_val_1, DEFAULT_ABS_TOL, DEFAULT_REL_TOL)) {
        failures++;
    }

    double expected_deriv_1 = cos(1.0) - sin(1.0);
    if (activation_derivative(&sinc, 1.0, &dy_pos) != ACTIVATION_STATUS_OK ||
        activation_derivative(&sinc, -1.0, &dy_neg) != ACTIVATION_STATUS_OK ||
        !almost_equal(dy_pos, expected_deriv_1, DEFAULT_ABS_TOL, DEFAULT_REL_TOL) ||
        !almost_equal(dy_neg, -expected_deriv_1, DEFAULT_ABS_TOL, DEFAULT_REL_TOL)) {
        failures++;
    }

    /* x = +-1e-8 */
    double x_small = 1e-8;
    double expected_val_small = 1.0 - (x_small * x_small) / 6.0;
    if (activation_value(&sinc, x_small, &y_pos) != ACTIVATION_STATUS_OK ||
        activation_value(&sinc, -x_small, &y_neg) != ACTIVATION_STATUS_OK ||
        !almost_equal(y_pos, expected_val_small, DEFAULT_ABS_TOL, DEFAULT_REL_TOL) ||
        !almost_equal(y_neg, expected_val_small, DEFAULT_ABS_TOL, DEFAULT_REL_TOL)) {
        failures++;
    }

    /* Особлива точність: abs_tol = 1e-16 */
    double expected_deriv_small = -x_small / 3.0;
    if (activation_derivative(&sinc, x_small, &dy_pos) != ACTIVATION_STATUS_OK ||
        activation_derivative(&sinc, -x_small, &dy_neg) != ACTIVATION_STATUS_OK ||
        !almost_equal(dy_pos, expected_deriv_small, STRICT_ZERO_TOL, 0.0) ||
        !almost_equal(dy_neg, -expected_deriv_small, STRICT_ZERO_TOL, 0.0)) {
        failures++;
    }

    /* NaN / Inf */
    double nan_out = 0.0;
    if (activation_value(&sinc, NAN, &nan_out) != ACTIVATION_STATUS_OK || !isnan(nan_out) ||
        activation_derivative(&sinc, INFINITY, &nan_out) != ACTIVATION_STATUS_OK || !isnan(nan_out)) {
        failures++;
    }

    if (failures > 0) {
        fprintf(stderr, "sinc_tests failed with %d error(s).\n", failures);
        return 1;
    }

    printf("All sinc_tests passed!\n");
    return 0;
}
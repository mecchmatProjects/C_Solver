
#include "miniai/ml/activation/tanh_activation.h"
#include <math.h>
#include <stdio.h>

static int failures = 0;

static void check_close(const char *name, double actual, double expected) {
    if (!isfinite(actual) || fabs(actual - expected) > 1e-12) {
        printf("FAIL: %s\n", name);
        failures++;
    } else {
        printf("PASS: %s\n", name);
    }
}

int main(void) {
    Activation activation;

    if (activation_tanh_init(NULL) != ACTIVATION_STATUS_INVALID_ARGUMENT) {
        printf("FAIL: NULL initializer\n");
        failures++;
    }

    if (activation_tanh_init(&activation) != ACTIVATION_STATUS_OK) {
        printf("FAIL: initialization\n");
        return 1;
    }

    const double x[] = {-1000.0, -1.0, 0.0, 1.0, 1000.0};

    const double expected_value[] = {
        -1.0, -0.7615941559557649, 0.0,
        0.7615941559557649, 1.0
    };

    const double expected_derivative[] = {
        0.0, 0.41997434161402614, 1.0,
        0.41997434161402614, 0.0
    };

    for (size_t i = 0; i < 5; ++i) {
        double value = NAN;
        double derivative = NAN;

        if (activation_value(&activation, x[i], &value)
                != ACTIVATION_STATUS_OK ||
            activation_derivative(&activation, x[i], &derivative)
                != ACTIVATION_STATUS_OK) {
            printf("FAIL: activation API at x=%g\n", x[i]);
            failures++;
            continue;
        }

        check_close("Tanh value", value, expected_value[i]);
        check_close("Tanh derivative", derivative, expected_derivative[i]);
    }

    double positive = NAN, negative = NAN;
    double d_positive = NAN, d_negative = NAN;

    if (activation_value(&activation, 1.0, &positive) == ACTIVATION_STATUS_OK &&
        activation_value(&activation, -1.0, &negative) == ACTIVATION_STATUS_OK) {
        check_close("Odd function", negative, -positive);
    } else {
        printf("FAIL: oddness API\n");
        failures++;
    }

    if (activation_derivative(&activation, 1.0, &d_positive) == ACTIVATION_STATUS_OK &&
        activation_derivative(&activation, -1.0, &d_negative) == ACTIVATION_STATUS_OK) {
        check_close("Even derivative", d_negative, d_positive);
    } else {
        printf("FAIL: derivative parity API\n");
        failures++;
    }

    if (activation_value(&activation, 0.0, NULL)
            != ACTIVATION_STATUS_INVALID_ARGUMENT) {
        printf("FAIL: NULL result\n");
        failures++;
    }

    if (failures == 0) {
        printf("All Tanh tests passed!\n");
    } else {
        printf("Failed tests: %d\n", failures);
    }

    return failures == 0 ? 0 : 1;
}

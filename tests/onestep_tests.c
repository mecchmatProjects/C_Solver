//
// Created by Katya on 31.10.2026.
//
#include <math.h>
#include <stdio.h>

#include "miniai/ml/activation/onestep.h"

static int same_result(double actual, double expected) {
    if (isnan(expected)) {
        return isnan(actual);
    }

    return actual == expected;
}

int main(void) {
    Activation activation = {0};

    double x[] = {-1.0, 0.0, 1.0, -1e-12, 1e-12, -0.0, NAN};
    double expected_value[] = {0.0, 1.0, 1.0, 0.0, 1.0, 1.0, NAN};
    double expected_derivative[] = {0.0, NAN, 0.0, 0.0, 0.0, NAN, NAN};

    if (activation_onestep_init(NULL) !=
        ACTIVATION_STATUS_INVALID_ARGUMENT) {
        printf("FAIL: NULL initializer\n");
        return 1;
        }

    if (activation_onestep_init(&activation) != ACTIVATION_STATUS_OK) {
        printf("FAIL: Onestep initialization\n");
        return 1;
    }

    for (int i = 0; i < 7; i++) {
        double value = NAN;
        double derivative = NAN;

        if (activation_value(&activation, x[i], &value) !=
            ACTIVATION_STATUS_OK) {
            printf("FAIL: value status for x = %g\n", x[i]);
            return 1;
            }

        if (!same_result(value, expected_value[i])) {
            printf("FAIL: value for x = %g: got %g, expected %g\n",
                   x[i], value, expected_value[i]);
            return 1;
        }

        if (activation_derivative(&activation, x[i], &derivative) !=
            ACTIVATION_STATUS_OK) {
            printf("FAIL: derivative status for x = %g\n", x[i]);
            return 1;
            }

        if (!same_result(derivative, expected_derivative[i])) {
            printf("FAIL: derivative for x = %g: got %g, expected %g\n",
                   x[i], derivative, expected_derivative[i]);
            return 1;
        }
    }

    printf("All Onestep tests passed\n");
    return 0;
}
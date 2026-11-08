//
// Created by Katya on 31.10.2026.
//
#include <math.h>
#include <stdio.h>

#include "miniai/ml/activation/onestep.h"

int main(void) {
    Activation activation = {0};
    double value = NAN;
    double derivative = NAN;

    if (activation_onestep_init(&activation) != ACTIVATION_STATUS_OK) {
        fprintf(stderr, "Initialization failed\n");
        return 1;
    }

    if (activation_value(&activation, 0.0, &value) != ACTIVATION_STATUS_OK ||
        activation_derivative(&activation, 0.0, &derivative) !=
        ACTIVATION_STATUS_OK) {
        fprintf(stderr, "Evaluation failed\n");
        return 1;
        }

    if (value != 1.0 || !isnan(derivative)) {
        fprintf(stderr, "Unexpected Onestep result at zero\n");
        return 1;
    }

    printf("Onestep(0) = %.1f\n", value);
    printf("Derivative at zero does not exist (NAN)\n");

    return 0;
}
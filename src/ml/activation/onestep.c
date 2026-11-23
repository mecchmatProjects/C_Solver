//
// Created by Katya on 15.10.2026.
//
#include <math.h>

#include "miniai/ml/activation/onestep.h"

static double onestep_value(const Activation *activation, double x) {
    (void)activation;

    if (isnan(x)) {
        return NAN;
    }

    if (x >= 0.0) {
        return 1.0;
    }

    return 0.0;
}

static double onestep_derivative(const Activation *activation, double x) {
    (void)activation;

    if (isnan(x) || x == 0.0) {
        return NAN;
    }

    return 0.0;
}

static const ActivationVTable ONESTEP_VTABLE = {
    onestep_value,
    onestep_derivative
};

ActivationStatus activation_onestep_init(Activation *activation) {
    if (activation == NULL) {
        return ACTIVATION_STATUS_INVALID_ARGUMENT;
    }

    activation->vtable = &ONESTEP_VTABLE;
    activation->parameter = 0.0;

    return ACTIVATION_STATUS_OK;
}
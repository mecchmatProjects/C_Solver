#include "miniai/ml/activation/gaussian.h"

#include <math.h>

static double gaussian_value(const Activation *activation, double x) {
    (void)activation;
    return exp(-(x * x));
}

static double gaussian_derivative(const Activation *activation, double x) {
    (void)activation;
    return -2.0 * x * exp(-(x * x));
}

static const ActivationVTable GAUSSIAN_VTABLE = {
    gaussian_value, gaussian_derivative};

ActivationStatus activation_gaussian_init(Activation *activation) {
    if (activation == NULL) {
        return ACTIVATION_STATUS_INVALID_ARGUMENT;
    }

    activation->vtable = &GAUSSIAN_VTABLE;
    activation->parameter = 0.0;
    return ACTIVATION_STATUS_OK;
}

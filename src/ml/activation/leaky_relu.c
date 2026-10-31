#include "miniai/ml/activation/leaky_relu.h"

#include <math.h>

static double leaky_relu_value(const Activation *activation, double x) {
    return x >= 0.0 ? x : activation->parameter * x;
}

static double leaky_relu_derivative(const Activation *activation, double x) {
    return x >= 0.0 ? 1.0 : activation->parameter;
}

static const ActivationVTable LEAKY_RELU_VTABLE = {
    leaky_relu_value, leaky_relu_derivative};

ActivationStatus activation_leaky_relu_init(Activation *activation,
                                            double negative_slope) {
    if (activation == NULL || !isfinite(negative_slope) ||
        negative_slope < 0.0) {
        return ACTIVATION_STATUS_INVALID_ARGUMENT;
    }

    activation->vtable = &LEAKY_RELU_VTABLE;
    activation->parameter = negative_slope;
    return ACTIVATION_STATUS_OK;
}

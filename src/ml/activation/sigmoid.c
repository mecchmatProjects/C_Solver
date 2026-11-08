#include "miniai/ml/activation/sigmoid.h"

#include <math.h>

static double sigmoid_value(const Activation *activation, double x) {
    (void)activation;
    if (x >= 0.0) {
        return 1.0 / (1.0 + exp(-x));
    }

    const double exp_x = exp(x);
    return exp_x / (1.0 + exp_x);
}

static double sigmoid_derivative(const Activation *activation, double x) {
    const double value = sigmoid_value(activation, x);
    return value * (1.0 - value);
}

static const ActivationVTable SIGMOID_VTABLE = {
    sigmoid_value, sigmoid_derivative};

ActivationStatus activation_sigmoid_init(Activation *activation) {
    if (activation == NULL) {
        return ACTIVATION_STATUS_INVALID_ARGUMENT;
    }

    activation->vtable = &SIGMOID_VTABLE;
    activation->parameter = 0.0;
    return ACTIVATION_STATUS_OK;
}

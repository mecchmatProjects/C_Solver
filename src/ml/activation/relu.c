#include "miniai/ml/activation/relu.h"

static double relu_value(const Activation *activation, double x) {
    (void)activation;
    return x < 0.0 ? 0.0 : x;
}

static double relu_derivative(const Activation *activation, double x) {
    (void)activation;
    return x > 0.0 ? 1.0 : 0.0;
}

static const ActivationVTable RELU_VTABLE = {relu_value, relu_derivative};

ActivationStatus activation_relu_init(Activation *activation) {
    if (activation == NULL) {
        return ACTIVATION_STATUS_INVALID_ARGUMENT;
    }

    activation->vtable = &RELU_VTABLE;
    activation->parameter = 0.0;
    return ACTIVATION_STATUS_OK;
}

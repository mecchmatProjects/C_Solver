
#include "miniai/ml/activation/tanh_activation.h"

#include <math.h>
#include <stddef.h>

static double tanh_value(const Activation *activation, double x) {
    (void)activation;
    return tanh(x);
}

static double tanh_derivative(const Activation *activation, double x) {
    (void)activation;
    double t = tanh(x);
    return 1.0 - t * t;
}

static const ActivationVTable TANH_VTABLE = {
    tanh_value,
    tanh_derivative
};

ActivationStatus activation_tanh_init(Activation *activation) {
    if (activation == NULL) {
        return ACTIVATION_STATUS_INVALID_ARGUMENT;
    }

    activation->vtable = &TANH_VTABLE;
    activation->parameter = 0.0;

    return ACTIVATION_STATUS_OK;
}

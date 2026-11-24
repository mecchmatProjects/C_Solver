#include "miniai/ml/activation/linear.h"

#include <math.h>

static double linear_value(const Activation *activation, double x) {
    (void)activation;
    return x;
}

static double linear_derivative(const Activation *activation, double x) {
    (void)activation;
    return isfinite(x) ? 1.0 : NAN;
}

static const ActivationVTable LINEAR_VTABLE = {linear_value,
                                               linear_derivative};

ActivationStatus activation_linear_init(Activation *activation) {
    if (activation == NULL) {
        return ACTIVATION_STATUS_INVALID_ARGUMENT;
    }

    activation->vtable = &LINEAR_VTABLE;
    activation->parameter = 0.0;
    return ACTIVATION_STATUS_OK;
}

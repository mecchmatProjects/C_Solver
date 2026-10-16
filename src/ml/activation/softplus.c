#include "miniai/ml/activation/softplus.h"

#include <math.h>

static double softplus_value(const Activation *activation, double x) {
    (void)activation;
    return fmax(x, 0.0) + log1p(exp(-fabs(x)));
}

static double softplus_derivative(const Activation *activation, double x) {
    if (x >= 0.0) {
        return 1.0 / (1.0 + exp(-x));
    }

    const double exp_x = exp(x);
    return exp_x / (1.0 + exp_x);
}

static const ActivationVTable SOFTPLUS_VTABLE = {
    softplus_value, softplus_derivative};

ActivationStatus activation_softplus_init(Activation *activation) {
    if (activation == NULL) {
        return ACTIVATION_STATUS_INVALID_ARGUMENT;
    }

    activation->vtable = &SOFTPLUS_VTABLE;
    activation->parameter = 0.0;
    return ACTIVATION_STATUS_OK;
}

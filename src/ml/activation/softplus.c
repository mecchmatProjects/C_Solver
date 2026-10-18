#include "miniai/ml/activation/softplus.h"
#include <math.h>

static double softplus_value(const Activation *activation, double x) {
    (void)activation;
    if (x > 20.0) {
        return x;
    }
    return log(1.0 + exp(x));
}

static double softplus_derivative(const Activation *activation, double x) {
    (void)activation;
    if (x > 20.0) {
        return 1.0;
    }
    if (x < -20.0) {
        return 0.0;
    }
    double exp_x = exp(x);
    return exp_x / (1.0 + exp_x);
}

static const ActivationVTable SOFTPLUS_VTABLE = {softplus_value, softplus_derivative};

ActivationStatus activation_softplus_init(Activation *activation) {
    if (activation == NULL) {
        return ACTIVATION_STATUS_INVALID_ARGUMENT;
    }
    activation->vtable = &SOFTPLUS_VTABLE;
    activation->parameter = 0.0;
    return ACTIVATION_STATUS_OK;
}

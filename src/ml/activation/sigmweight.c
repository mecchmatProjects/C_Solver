#include "miniai/ml/activation/sigmweight.h"

#include <math.h>

static double sigmweight_value(const Activation *activation, double x) {
    (void)activation;
    return x / (1.0 + exp(-x));
}

static double sigmweight_derivative(const Activation *activation, double x) {
    (void)activation;
    double exp_nx = exp(-x);
    double denom = 1.0 + exp_nx;
    return (1.0 + (x + 1.0) * exp_nx) / (denom * denom);
}

static const ActivationVTable SIGMWEIGHT_VTABLE = {sigmweight_value, sigmweight_derivative};

ActivationStatus activation_sigmweight_init(Activation *activation) {
    if (activation == NULL) {
        return ACTIVATION_STATUS_INVALID_ARGUMENT;
    }
    
    activation->vtable = &SIGMWEIGHT_VTABLE;
    activation->parameter = 0.0;
    return ACTIVATION_STATUS_OK;
}

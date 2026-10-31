#include <math.h>
#include <stddef.h>

#include "miniai/ml/activation/sigmweight.h"

static double sigmweight_value(const Activation *activation, double x) {
    (void)activation;
    return x / (1.0 + exp(-x));
}

static double sigmweight_derivative(const Activation *activation, double x) {
    (void)activation;
    double sig = 1.0 / (1.0 + exp(-x));
    return sig + x * sig * (1.0 - sig);
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

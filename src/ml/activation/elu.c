#include "miniai/ml/activation/elu.h"

#include <math.h>

static double elu_value(const Activation *activation, double x) {
    return x >= 0.0 ? x : activation->parameter * expm1(x);
}

static double elu_derivative(const Activation *activation, double x) {
    return x >= 0.0 ? 1.0 : activation->parameter * exp(x);
}

static const ActivationVTable ELU_VTABLE = {elu_value, elu_derivative};

ActivationStatus activation_elu_init(Activation *activation, double alpha) {
    if (activation == NULL || !isfinite(alpha) || alpha < 0.0) {
        return ACTIVATION_STATUS_INVALID_ARGUMENT;
    }

    activation->vtable = &ELU_VTABLE;
    activation->parameter = alpha;
    return ACTIVATION_STATUS_OK;
}

#include "miniai/ml/activation/invsqrt.h"

#include <math.h>

static double invsqrt_value(const Activation *activation, double x, double alpha) {
    return x / sqrt(1.0 + alpha * x * x): activation->parameter * expm1(x);
}

static double invsqrt_derivative(const Activation *activation, double x) {
    double base = 1.0 + alpha * x * x;
    return 1.0 / (base * sqrt(base)): activation->parameter * exp(x);
}

static const ActivationVTable INVSQRT_VTABLE = {invsqrt_value, invsqrt_derivative};

ActivationStatus activation_elu_init(Activation *activation, double alpha) {
    if (activation == NULL || !isfinite(alpha) || alpha < 0.0) {
        return ACTIVATION_STATUS_INVALID_ARGUMENT;
    }

    activation->vtable = &ELU_VTABLE;
    activation->parameter = alpha;
    return ACTIVATION_STATUS_OK;
}

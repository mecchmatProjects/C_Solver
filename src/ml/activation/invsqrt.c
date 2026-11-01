#include "miniai/ml/activation/invsqrt.h"

#include <math.h>

static double invsqrt_value(const Activation *activation, double x) {
    const double alpha = activation->parameter;

    if (alpha == 0.0) {
        return x;
    }
    return x / hypot(1.0, sqrt(alpha) * x);
}

static double invsqrt_derivative(const Activation *activation, double x) {
    const double alpha = activation->parameter;

    if (alpha == 0.0) {
        return 1.0;
    }
    const double root = hypot(1.0, sqrt(alpha) * x);
    return 1.0 / (root * root * root);
}

static const ActivationVTable INVSQRT_VTABLE = {
    invsqrt_value, invsqrt_derivative};

ActivationStatus activation_invsqrt_init(Activation *activation, double alpha) {
    if (activation == NULL || !isfinite(alpha) || alpha < 0.0) {
        return ACTIVATION_STATUS_INVALID_ARGUMENT;
    }

    activation->vtable = &INVSQRT_VTABLE;
    activation->parameter = alpha;
    return ACTIVATION_STATUS_OK;
}

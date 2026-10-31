#include "miniai/ml/activation/soft_exponential.h"

#include <float.h>
#include <math.h>

static double soft_exponential_value(const Activation *activation, double x) {
    double a = activation->parameter;

    if (a < 0.0) {
        return -log(1.0 - a * (x + a)) / a;
    } else if (a == 0.0) {
        return x;
    } else {
        return (exp(a * x) - 1.0) / a + a;
    }
}

static double soft_exponential_derivative(const Activation *activation, double x) {
    double a = activation->parameter;

    if (a < 0.0) {
        double denom = 1.0 - a * (x + a);
        if (denom <= 0.0) return DBL_MAX;
        return 1.0 / denom;
    } else if (a == 0.0) {
        return 1.0;
    } else {
        return exp(a * x);
    }
}

static const ActivationVTable SOFT_EXPONENTIAL_VTABLE = {
    soft_exponential_value, soft_exponential_derivative
};

ActivationStatus activation_soft_exponential_init(Activation *activation, double alpha) {
    if (activation == NULL || !isfinite(alpha)) {
        return ACTIVATION_STATUS_INVALID_ARGUMENT;
    }

    activation->vtable = &SOFT_EXPONENTIAL_VTABLE;
    activation->parameter = alpha;
    return ACTIVATION_STATUS_OK;
}

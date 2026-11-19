#include "miniai/ml/activation/sinc.h"
#include <math.h>

#define SINC_TAYLOR_THRESHOLD 1e-3

static double sinc_value(const Activation *activation, double x) {
    (void)activation;
    if (!isfinite(x)) {
        return NAN;
    }

    if (fabs(x) < SINC_TAYLOR_THRESHOLD) {
        double x2 = x * x;
        return 1.0 - (x2 / 6.0) + ((x2 * x2) / 120.0);
    }

    return sin(x) / x;
}

static double sinc_derivative(const Activation *activation, double x) {
    (void)activation;
    if (!isfinite(x)) {
        return NAN;
    }

    if (fabs(x) < SINC_TAYLOR_THRESHOLD) {
        double x2 = x * x;
        return (-x / 3.0) + ((x * x2) / 30.0);
    }

    return (x * cos(x) - sin(x)) / (x * x);
}

static const ActivationVTable SINC_VTABLE = {sinc_value, sinc_derivative};

ActivationStatus activation_sinc_init(Activation *activation) {
    if (activation == NULL) {
        return ACTIVATION_STATUS_INVALID_ARGUMENT;
    }

    activation->vtable = &SINC_VTABLE;
    activation->parameter = 0.0;
    return ACTIVATION_STATUS_OK;
}
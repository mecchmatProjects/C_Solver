#include "miniai/ml/activation/bent.h"

#include <math.h>

static double bent_value(const Activation *activation, double x) {
    (void)activation;
    return x + 0.5 * (hypot(x, 1.0) - 1.0);
}

static double bent_derivative(const Activation *activation, double x) {
    (void)activation;
    return 1.0 + 0.5 * (x / hypot(x, 1.0));
}

static const ActivationVTable BENT_VTABLE = {bent_value, bent_derivative};

ActivationStatus activation_bent_init(Activation *activation) {
    if (activation == NULL) {
        return ACTIVATION_STATUS_INVALID_ARGUMENT;
    }

    activation->vtable = &BENT_VTABLE;
    activation->parameter = 0.0;
    return ACTIVATION_STATUS_OK;
}

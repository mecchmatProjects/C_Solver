#include "miniai/ml/activation/softsign.h"

#include <math.h>

static double softsign_value(const Activation *activation, double x) {
    (void)activation;
    return x / (1.0 + fabs(x));
}

static double softsign_derivative(const Activation *activation, double x) {
    (void)activation;
    const double denominator = 1.0 + fabs(x);
    return 1.0 / (denominator * denominator);
}

static const ActivationVTable SOFTSIGN_VTABLE = {
    softsign_value, softsign_derivative};

ActivationStatus activation_softsign_init(Activation *activation) {
    if (activation == NULL) {
        return ACTIVATION_STATUS_INVALID_ARGUMENT;
    }

    activation->vtable = &SOFTSIGN_VTABLE;
    activation->parameter = 0.0;
    return ACTIVATION_STATUS_OK;
}

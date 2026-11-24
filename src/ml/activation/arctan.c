#include "miniai/ml/activation/arctan.h"

#include <math.h>

static double arctan_value(const Activation *activation, double x) {
    (void)activation;
    return atan(x);
}

static double arctan_derivative(const Activation *activation, double x) {
    (void)activation;
    return 1.0 / (1.0 + x * x);
}

static const ActivationVTable ARCTAN_VTABLE = {
    arctan_value, arctan_derivative};

ActivationStatus activation_arctan_init(Activation *activation) {
    if (activation == NULL) {
        return ACTIVATION_STATUS_INVALID_ARGUMENT;
    }

    activation->vtable = &ARCTAN_VTABLE;
    activation->parameter = 0.0;
    return ACTIVATION_STATUS_OK;
}

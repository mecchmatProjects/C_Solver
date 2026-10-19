#include "miniai/ml/activation/arctan.h"

#include <math.h>

static double arctan_value(const Activation *activation, double x) {
    (void)activation;
    double epsilon = 1e-9;
    double result = 0.0;
    double term = x;
    int n = 1;

    while (fabs(term) > epsilon) {
        result += term;
        term *= -x * x * (2 * n - 1) / (2 * n + 1);
        n++;
    }
    
    return result;
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

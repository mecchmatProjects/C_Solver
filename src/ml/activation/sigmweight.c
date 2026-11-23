#include <stddef.h>

#include "miniai/ml/activation/sigmoid.h"
#include "miniai/ml/activation/sigmweight.h"

static double eval_sigmoid(const double x) {
    Activation sigmoid_act;
    double s = 0.0;

    if (activation_sigmoid_init(&sigmoid_act) != ACTIVATION_STATUS_OK) {
        return 0.0;
    }
    if (activation_value(&sigmoid_act, x, &s) != ACTIVATION_STATUS_OK) {
        return 0.0;
    }

    return s;
}

static double sigmweight_value(const Activation *activation, const double x) {
    (void)activation;
    const double s = eval_sigmoid(x);
    return x * s;
}

static double sigmweight_derivative(const Activation *activation, const double x) {
    (void)activation;
    const double s = eval_sigmoid(x);
    return s + x * s * (1.0 - s);
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
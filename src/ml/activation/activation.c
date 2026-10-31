#include "miniai/ml/activation/activation.h"

ActivationStatus activation_value(const Activation *activation, double x,
                                  double *result) {
    if (activation == NULL || result == NULL || activation->vtable == NULL ||
        activation->vtable->value == NULL) {
        return ACTIVATION_STATUS_INVALID_ARGUMENT;
    }

    *result = activation->vtable->value(activation, x);
    return ACTIVATION_STATUS_OK;
}

ActivationStatus activation_derivative(const Activation *activation, double x,
                                       double *result) {
    if (activation == NULL || result == NULL || activation->vtable == NULL ||
        activation->vtable->derivative == NULL) {
        return ACTIVATION_STATUS_INVALID_ARGUMENT;
    }

    *result = activation->vtable->derivative(activation, x);
    return ACTIVATION_STATUS_OK;
}

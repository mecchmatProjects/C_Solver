#ifndef MINIAI_ML_ACTIVATION_ACTIVATION_H
#define MINIAI_ML_ACTIVATION_ACTIVATION_H

#include <stddef.h>

typedef struct Activation Activation;

typedef double (*ActivationScalarFunction)(const Activation *activation,
                                           double x);

typedef struct {
    ActivationScalarFunction value;
    ActivationScalarFunction derivative;
} ActivationVTable;

struct Activation {
    const ActivationVTable *vtable;
    double parameter;
};

typedef enum {
    ACTIVATION_STATUS_OK = 0,
    ACTIVATION_STATUS_INVALID_ARGUMENT
} ActivationStatus;

ActivationStatus activation_value(const Activation *activation, double x,
                                  double *result);
ActivationStatus activation_derivative(const Activation *activation, double x,
                                       double *result);

#endif

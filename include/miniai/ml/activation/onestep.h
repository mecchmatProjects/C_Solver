#ifndef MINIAI_ML_ACTIVATION_ONESTEP_H
#define MINIAI_ML_ACTIVATION_ONESTEP_H

#include "miniai/ml/activation/activation.h"

/*
 * Onestep: f(x) = 0 for x < 0, otherwise 1.
 * For real x != 0, the derivative is 0.
 * At x == 0, the derivative does not exist: returns NAN.
 * NAN input produces NAN for both value and derivative.
 *
 * Evaluate through activation_value() and activation_derivative().
 * Their OK status does not guarantee a finite mathematical result.
 *
 * Initialization returns ACTIVATION_STATUS_INVALID_ARGUMENT
 * if activation is NULL; otherwise ACTIVATION_STATUS_OK.
 */
ActivationStatus activation_onestep_init(Activation *activation);

#endif
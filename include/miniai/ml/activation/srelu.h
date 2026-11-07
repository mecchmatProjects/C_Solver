#ifndef MINIAI_ML_ACTIVATION_SRELU_H
#define MINIAI_ML_ACTIVATION_SRELU_H

#include "miniai/ml/activation/activation.h"

/* Lab 2 A5: declarations only. Four parameters do not fit Activation.
 * Require finite arguments, tl < tr, al/ar >= 0, and non-NULL result.
 * On invalid input return INVALID_ARGUMENT without modifying result.
 * The chosen derivative at tl/tr is 1.
 */
ActivationStatus activation_srelu_value(double x, double tl, double tr,
                                        double al, double ar, double *result);
ActivationStatus activation_srelu_derivative(double x, double tl, double tr,
                                             double al, double ar, double *result);

#endif

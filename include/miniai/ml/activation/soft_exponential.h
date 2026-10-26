#ifndef MINIAI_ML_ACTIVATION_SOFT_EXPONENTIAL_H
#define MINIAI_ML_ACTIVATION_SOFT_EXPONENTIAL_H

#include "miniai/ml/activation/activation.h"

/* Lab 2 A1: declaration only. Alpha must be finite.
 * For alpha < 0, value and derivative return NAN outside
 * 1 - alpha * (x + alpha) > 0.
 */
ActivationStatus activation_soft_exponential_init(Activation *activation,
                                                 double alpha);

#endif

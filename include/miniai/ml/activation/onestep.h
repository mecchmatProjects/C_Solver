#ifndef MINIAI_ML_ACTIVATION_ONESTEP_H
#define MINIAI_ML_ACTIVATION_ONESTEP_H

#include "miniai/ml/activation/activation.h"

/* Lab 2 A2: declaration only. The derivative at exactly zero returns NAN. */
ActivationStatus activation_onestep_init(Activation *activation);

#endif

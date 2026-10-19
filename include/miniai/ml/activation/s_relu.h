#ifndef MINIAI_ML_ACTIVATION_S_RELU_H
#define MINIAI_ML_ACTIVATION_S_RELU_H

#include "miniai/ml/activation/activation.h"

ActivationStatus activation_s_relu_init(Activation *activation,
                                        double tl, double tr,
                                        double al, double ar);

#endif

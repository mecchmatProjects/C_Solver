#ifndef MINIAI_ML_ACTIVATION_LEAKY_RELU_H
#define MINIAI_ML_ACTIVATION_LEAKY_RELU_H

#include "miniai/ml/activation/activation.h"

ActivationStatus activation_leaky_relu_init(Activation *activation,
                                            double negative_slope);

#endif

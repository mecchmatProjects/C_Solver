#ifndef MINIAI_ML_ACTIVATION_LINEAR_H
#define MINIAI_ML_ACTIVATION_LINEAR_H

#include "miniai/ml/activation/activation.h"

/* Lab 2 A9: Linear (identity) activation.
 *
 * value:      f(x)  = x
 * derivative: f'(x) = 1 for every finite x
 *
 * Behaviour of the math callbacks outside finite inputs:
 *   - value returns x unchanged, so NaN -> NaN, +Inf -> +Inf, -Inf -> -Inf,
 *     and the sign of zero is preserved (f(-0.0) == -0.0).
 *   - derivative returns NAN for NaN and +/-Inf: the derivative is defined
 *     only at finite points, so no value is claimed at infinity.
 * ACTIVATION_STATUS_OK from activation_value()/activation_derivative()
 * confirms a valid interface call, not that the result is finite.
 *
 * activation_linear_init() returns ACTIVATION_STATUS_INVALID_ARGUMENT for a
 * NULL activation and ACTIVATION_STATUS_OK otherwise.
 */
ActivationStatus activation_linear_init(Activation *activation);

#endif

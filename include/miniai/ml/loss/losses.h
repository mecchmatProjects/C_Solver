#ifndef MINIAI_ML_LOSS_LOSSES_H
#define MINIAI_ML_LOSS_LOSSES_H

#include <stddef.h>

/*
 * Loss API (Lab 2, B1).
 *
 * Scalar naming: miniai_squared_error is the loss for one pair
 * (prediction, target). MSE is the vector mean and is a separate function.
 *
 * Common rules for scalar losses and their derivatives:
 *  - derivatives are taken with respect to prediction;
 *  - prediction and target must be finite, otherwise the result is NAN;
 *  - NAN is the only error signal, callers must check it with isnan().
 */

/* L = (p - y)^2,  dL/dp = 2(p - y) */
double miniai_squared_error(double prediction, double target);
double miniai_squared_error_derivative(double prediction, double target);

/* L = |p - y|,  dL/dp = sign(p - y); subgradient 0 is used when p == y */
double miniai_absolute_error(double prediction, double target);
double miniai_absolute_error_derivative(double prediction, double target);

/*
 * L = -[y ln(p_c) + (1 - y) ln(1 - p_c)],  dL/dp = -y/p_c + (1 - y)/(1 - p_c)
 * p and y must be in [0, 1] (soft labels allowed), otherwise NAN.
 * p_c = clip(p, eps, 1 - eps), eps = 1e-12.
 * The derivative is computed at the clipped p_c. It is not the derivative
 * of the clipped composite, which would be 0 on the saturated parts.
 */
double miniai_binary_cross_entropy(double prediction, double target);
double miniai_binary_cross_entropy_derivative(double prediction, double target);

/*
 * e = p - y
 * L = 0.5 e^2 for |e| <= delta, delta(|e| - 0.5 delta) otherwise
 * dL/dp = e for |e| <= delta, delta sign(e) otherwise
 * delta must be finite and > 0, otherwise NAN.
 */
double miniai_huber_loss(double prediction, double target, double delta);
double miniai_huber_loss_derivative(double prediction, double target, double delta);

/*
 * e = p - y
 * L = ln(cosh(e)) = |e| + log1p(exp(-2|e|)) - ln 2,  dL/dp = tanh(e)
 */
double miniai_log_cosh_loss(double prediction, double target);
double miniai_log_cosh_loss_derivative(double prediction, double target);

/*
 * Vector losses (Lab 3): mean of the scalar loss over n pairs.
 * n == 0, NULL arrays or non-finite data give NAN.
 */
double miniai_mse(const double pred[], const double target[], size_t n);
double miniai_mae(const double pred[], const double target[], size_t n);

#endif

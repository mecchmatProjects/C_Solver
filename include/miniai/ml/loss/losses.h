#ifndef MINIAI_ML_LOSS_LOSSES_H
#define MINIAI_ML_LOSS_LOSSES_H

#include <stddef.h>

/*
 * Loss API contract (Lab 2).
 *
 * All scalar loss functions and their derivatives:
 * - require finite prediction and target values;
 * - return NAN for invalid arguments.
 *
 * Squared error:
 *   L = (prediction - target)^2
 *
 * Absolute error:
 *   L = |prediction - target|
 *   Its derivative is 0 when prediction == target.
 *
 * Binary cross entropy:
 * - prediction and target must belong to [0, 1];
 * - prediction is clipped to [1e-12, 1 - 1e-12];
 * - derivative is calculated with respect to the clipped prediction.
 *
 * Huber loss:
 * - delta must be finite and strictly positive.
 *
 * Log-cosh loss:
 * - prediction and target must be finite.
 *
 * Vector losses (MSE and MAE):
 * - require n > 0;
 * - require non-NULL arrays containing finite values;
 * - return NAN for invalid arguments.
 *
 * All derivatives are calculated with respect to prediction.
 */
double miniai_squared_error(double prediction, double target);
double miniai_squared_error_derivative(double prediction, double target);
double miniai_absolute_error(double prediction, double target);
double miniai_absolute_error_derivative(double prediction, double target);
double miniai_binary_cross_entropy(double prediction, double target);
double miniai_binary_cross_entropy_derivative(double prediction, double target);
double miniai_huber_loss(double prediction, double target, double delta);
double miniai_huber_loss_derivative(double prediction, double target, double delta);
double miniai_log_cosh_loss(double prediction, double target);
double miniai_log_cosh_loss_derivative(double prediction, double target);
double miniai_mse(const double pred[], const double target[], size_t n);
double miniai_mae(const double pred[], const double target[], size_t n);

#endif

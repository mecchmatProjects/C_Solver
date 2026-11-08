#ifndef MINIAI_ML_LOSS_LOSSES_H
#define MINIAI_ML_LOSS_LOSSES_H

#include <stddef.h>

/* Lab 2/3 declarations only; student implementations are not provided yet.
 * Invalid scalar inputs (including non-finite values) return NAN.
 * BCE requires prediction and target in [0,1]; clip prediction to
 * [1e-12,1-1e-12]. Its derivative is with respect to the clipped prediction.
 * Huber requires finite delta > 0. Absolute error uses subgradient 0 at equality.
 * Vector losses require n > 0 and non-NULL, finite input data; otherwise NAN.
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

#include "miniai/ml/loss/losses.h"

#include <math.h>

double miniai_huber_loss(double prediction, double target, double delta) {
    double error;
    double absolute_error;

    if (!isfinite(prediction) || !isfinite(target) || !isfinite(delta) ||
        delta <= 0.0) {
        return NAN;
    }

    error = prediction - target;
    absolute_error = fabs(error);

    if (absolute_error <= delta) {
        return 0.5 * error * error;
    }

    return delta * (absolute_error - 0.5 * delta);
}
#include <math.h>

#include "miniai/ml/loss/losses.h"

double miniai_mse(const double pred[], const double target[], size_t n) {
    size_t index;
    double mean = 0.0;

    /* MSE averages squared error across the prediction-target pairs.
     * Each pair's loss comes from the shared scalar squared-error function.
     * Empty inputs and null arrays are invalid and return NAN.
     * Non-finite elements or a non-finite scalar loss also return NAN.
     * The running mean avoids storing all per-element losses in another array.
     */
    if (n == 0 || pred == NULL || target == NULL) {
        return NAN;
    }

    for (index = 0; index < n; ++index) {
        double squared_error;

        if (!isfinite(pred[index]) || !isfinite(target[index])) {
            return NAN;
        }

        squared_error = miniai_squared_error(pred[index], target[index]);
        if (!isfinite(squared_error)) {
            return NAN;
        }

        mean += (squared_error - mean) / (double)(index + 1);
    }

    return mean;
}

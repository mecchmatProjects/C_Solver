#include "miniai/gradient_check.h"

#include <math.h>

double miniai_gradient_max_abs_error(const double exact[],
                                     const double approx[], size_t n) {
    if (n == 0 || exact == NULL || approx == NULL) {
        return NAN;
    }

    double max_error = 0.0;
    for (size_t i = 0; i < n; ++i) {
        if (!isfinite(exact[i]) || !isfinite(approx[i])) {
            return NAN;
        }

        const double error = fabs(exact[i] - approx[i]);
        if (error > max_error) {
            max_error = error;
        }
    }

    return max_error;
}

double miniai_gradient_max_rel_error(const double exact[],
                                     const double approx[], size_t n,
                                     double floor) {
    if (n == 0 || exact == NULL || approx == NULL || !isfinite(floor) ||
        floor <= 0.0) {
        return NAN;
    }

    double max_error = 0.0;
    for (size_t i = 0; i < n; ++i) {
        if (!isfinite(exact[i]) || !isfinite(approx[i])) {
            return NAN;
        }

        double denominator = fabs(exact[i]);
        if (denominator < floor) {
            denominator = floor;
        }

        double difference = exact[i] - approx[i];
        double relative_error;
        if (isfinite(difference)) {
            relative_error = fabs(difference) / denominator;
        } else {
            relative_error =
                fabs(exact[i] / denominator - approx[i] / denominator);
        }

        if (relative_error > max_error) {
            max_error = relative_error;
        }
    }

    return max_error;
}

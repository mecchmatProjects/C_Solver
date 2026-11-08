#include "miniai/math/statistics.h"
#include <math.h>

double miniai_mean(const double data[], size_t n) {
    if (data == NULL || n == 0) {
        return NAN;
    }

    double sum = 0.0;

    for (size_t i = 0; i < n; ++i) {
        if (!isfinite(data[i])) {
            return NAN;
        }

        sum += data[i];
    }

    return sum / (double)n;
}
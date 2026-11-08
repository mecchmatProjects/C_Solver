#include "miniai/math/vector.h"

#include <math.h>
#include <stddef.h>

int miniai_vector_subtract(const double a[], const double b[], double out[],
                           size_t n) {
    size_t index;

    if (n == 0) {
        return 0;
    }
    if (a == NULL || b == NULL || out == NULL) {
        return 1;
    }

    for (index = 0; index < n; ++index) {
        out[index] = a[index] - b[index];
    }
    return 0;
}

double miniai_vector_sum(const double v[], size_t n) {
    if (v == NULL || n == 0) {
        return 0.0;
    }

    double sum = 0.0;

    for (size_t i = 0; i < n; ++i) {
        sum += v[i];
    }

    return sum;
}

double miniai_vector_distance(const double a[], const double b[], size_t n) {
    if (n == 0) {
        return 0.0;
    }

    if (a == NULL || b == NULL) {
        return NAN;
    }

    double scale = 0.0;
    double sumsq = 1.0;

    for (size_t i = 0; i < n; ++i) {
        if (!isfinite(a[i]) || !isfinite(b[i])) {
            return NAN;
        }

        double diff = fabs(a[i] - b[i]);
        if (!isfinite(diff)) {
            return NAN;
        }

        if (diff > 0.0) {
            if (scale < diff) {
                double ratio = scale / diff;
                sumsq = 1.0 + sumsq * ratio * ratio;
                scale = diff;
            } else {
                double ratio = diff / scale;
                sumsq += ratio * ratio;
            }
        }
    }

    return scale * sqrt(sumsq);
}

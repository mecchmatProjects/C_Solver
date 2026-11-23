#include "miniai/math/statistics.h"

#include <math.h>
#include <stddef.h>

double miniai_min(const double data[], size_t n)
{
    if (n == 0 || data == NULL) {
        return NAN;
    }

    double minimum = data[0];
    if (!isfinite(minimum)) {
        return NAN;
    }

    for (size_t i = 1; i < n; ++i) {
        if (!isfinite(data[i])) {
            return NAN;
        }
        if (data[i] < minimum) {
            minimum = data[i];
        }
    }

    return minimum;
}

double miniai_max(const double data[], size_t n)
{
    if (n == 0 || data == NULL) {
        return NAN;
    }

    double maximum = data[0];
    if (!isfinite(maximum)) {
        return NAN;
    }

    for (size_t i = 1; i < n; ++i) {
        if (!isfinite(data[i])) {
            return NAN;
        }
        if (data[i] > maximum) {
            maximum = data[i];
        }
    }

    return maximum;
}

int miniai_minmax_scale(const double in[], double out[], size_t n)
{
    if (n == 0 || in == NULL || out == NULL) {
        return 1;
    }

    double minimum = miniai_min(in, n);
    double maximum = miniai_max(in, n);
    if (isnan(minimum) || isnan(maximum) || maximum == minimum) {
        return 1;
    }

    double range = maximum - minimum;
    if (!isfinite(range)) {
        return 1;
    }

    for (size_t i = 0; i < n; ++i) {
        out[i] = (in[i] - minimum) / range;
    }

    return 0;
}

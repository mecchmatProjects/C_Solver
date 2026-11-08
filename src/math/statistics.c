
#include "miniai/math/statistics.h"
#include <math.h>

double miniai_mean(const double data[], size_t n) {
    if (n == 0 || data == NULL) return NAN;

    double sum = 0.0;

    for ( size_t i = 0; i < n; ++i ) {
        sum += data[i];
    }

    return sum / n;
}


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
double miniai_variance( const double data[], size_t n ) {
    double sum = 0.0;
    if ( n == 0 || data == NULL ) {
        return NAN;
    }
    double mean = miniai_mean( data, n );
    for ( size_t i = 0; i < n; i++ ) {
        double diff = data[i] - mean;
        sum += diff * diff;
    }

    return sum/n;
}

double miniai_stddev( const double data[], size_t n ) {
    double val = miniai_variance(data, n);
    if ( n == 0 || data == NULL ) {
        return NAN;
    }
    else {
        return sqrt(val);
    }
}
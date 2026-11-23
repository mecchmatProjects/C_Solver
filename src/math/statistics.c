#include "miniai/math/statistics.h"
#include <math.h>
#include <stddef.h>


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

/* 
    Standardizes the input array to have a mean of 0 and stddev of 1.
    Formula: (x_i - mean) / stddev
    Supports in-place operations if in == out.
*/
int miniai_standardize(const double in[], double out[], size_t n) {
    size_t index;
    double stddev;
    double mean;

    // Requirement: n=0 -> error
    if (n == 0) {
        return 1;
    }

    if (in == NULL || out == NULL){
        return 2;
    }
    stddev = miniai_stddev(in, n);

    // Requirement: std==0 -> error. Also handle NaN to avoid division by zero
    if (!isfinite(stddev) || stddev == 0.0) {
        return 3;
    }
    mean = miniai_mean(in, n);

    for (index = 0; index < n; ++index) {
        out[index] = (in[index] - mean) / stddev;
    }

    return 0;
}
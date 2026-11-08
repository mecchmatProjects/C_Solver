#include "miniai/math/statistics.h"
#include <math.h>
#include <stddef.h>

// ===================================
// TEMPORARY MOCKS FOR DEPENDENCIES (B1 & B5)
// Delete these two functions when B1 and B5 are merged!
double miniai_mean(const double in[], size_t n) {
    size_t index;
    double sum = 0.0;

    if (in == NULL || n == 0) {
        return NAN;
    }

    for (index = 0; index < n; ++index) {
        sum += in[index];
    }
    return sum / (double)n;
}

double miniai_stddev(const double in [], size_t n) {
    size_t index;
    double m;
    double sum_sq = 0.0;

    if (in == NULL || n <= 1) {
        return NAN;
    }
    m = miniai_mean(in, n);
    for (index = 0; index < n; ++index){
        sum_sq += (in[index] - m) * (in[index] - m);
    }
    return sqrt(sum_sq / (double)(n - 1));
}
// ===================================

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
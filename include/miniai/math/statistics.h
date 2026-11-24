#ifndef MINIAI_MATH_STATISTICS_H
#define MINIAI_MATH_STATISTICS_H

#include <stddef.h>

/* Lab 3 declarations only. Scalar statistics return NAN for n == 0,
 * NULL data, or non-finite elements. Variance is population variance.
 * Transformations: 0 means success, nonzero means error; in-place is allowed.
 * Empty/invalid data and zero range/stddev are errors; leave output unchanged.
 * Output has capacity n; partial overlap is unsupported.
 */
double miniai_mean(const double data[], size_t n);
double miniai_min(const double data[], size_t n);
double miniai_max(const double data[], size_t n);
double miniai_variance(const double data[], size_t n);
double miniai_stddev(const double data[], size_t n);
int miniai_minmax_scale(const double in[], double out[], size_t n);
int miniai_standardize(const double in[], double out[], size_t n);

#endif

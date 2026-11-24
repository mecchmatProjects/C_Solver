#ifndef MINIAI_MATH_STATISTICS_H
#define MINIAI_MATH_STATISTICS_H

#include <stddef.h>


/**
 * @brief Calculates the arithmetic mean of an array.
 *
 * Formula: mean = Σxᵢ / n.
 *
 * @param data Input array of double values.
 * @param n Number of elements in the array.
 * @return Arithmetic mean, or NAN if n == 0, data is NULL,
 *         or any element is not finite.
 */
double miniai_mean(const double data[], size_t n);
double miniai_min(const double data[], size_t n);
double miniai_max(const double data[], size_t n);
double miniai_variance(const double data[], size_t n);
double miniai_stddev(const double data[], size_t n);
int miniai_minmax_scale(const double in[], double out[], size_t n);
int miniai_standardize(const double in[], double out[], size_t n);

#endif

#ifndef MINIAI_GRADIENT_CHECK_H
#define MINIAI_GRADIENT_CHECK_H

#include <stddef.h>

/*
 * Compare two finite gradient vectors with n > 0.
 * Invalid pointers, empty vectors, non-finite elements, or a non-finite or
 * non-positive floor make either function return NAN.
 * Absolute error is max_i |exact[i] - approx[i]|.
 * Relative error is max_i |exact[i] - approx[i]| /
 * max(|exact[i]|, floor). A result that exceeds the double range is INFINITY.
 */
double miniai_gradient_max_abs_error(const double exact[],
                                     const double approx[], size_t n);
double miniai_gradient_max_rel_error(const double exact[],
                                     const double approx[], size_t n,
                                     double floor);

#endif

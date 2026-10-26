#ifndef MINIAI_MATH_VECTOR_H
#define MINIAI_MATH_VECTOR_H

#include <stddef.h>

/* Lab 3 declarations only. Inputs have n elements; output has capacity n.
 * With n == 0, sum/dot/norm/distance return 0; add/subtract/scale and
 * activation transforms return success without accessing pointers.
 * Otherwise NULL pointers are invalid: scalar results return NAN,
 * int results return nonzero (0 means success).
 * Elementwise output may equal an input; partial overlap is unsupported.
 * Cosine similarity on empty/zero vectors returns NAN.
 * Normalization on empty/zero vectors returns an error without writing output.
 */
double miniai_vector_sum(const double v[], size_t n);
int miniai_vector_add(const double a[], const double b[], double out[], size_t n);
int miniai_vector_subtract(const double a[], const double b[], double out[], size_t n);
int miniai_vector_scale(const double in[], double alpha, double out[], size_t n);
double miniai_vector_dot(const double a[], const double b[], size_t n);
double miniai_vector_l1_norm(const double v[], size_t n);
double miniai_vector_l2_norm(const double v[], size_t n);
double miniai_vector_distance(const double a[], const double b[], size_t n);
double miniai_vector_cosine_similarity(const double a[], const double b[], size_t n);
int miniai_vector_normalize(const double in[], double out[], size_t n);
int miniai_vector_relu(const double in[], double out[], size_t n);
int miniai_vector_sigmoid(const double in[], double out[], size_t n);

#endif

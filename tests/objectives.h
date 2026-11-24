#ifndef MINIAI_OBJECTIVES_H
#define MINIAI_OBJECTIVES_H
#include <stddef.h>

int input_check(const double x[], size_t n, void *ctx, size_t *expected_n);
void fill_grad_nan(double g[], size_t n);
double miniai_test_quadratic(const double x[], size_t n, void *ctx);
void miniai_grad_quadratic(const double x[], double g[], size_t n, void *ctx);

double miniai_test_separable(const double x[], size_t n, void *ctx);
void miniai_grad_separable(const double x[], double g[], size_t n, void *ctx);

double miniai_test_bowl(const double x[], size_t n, void *ctx);
void miniai_grad_bowl(const double x[], double g[], size_t n, void *ctx);

void objectives_test();

#endif //MINIAI_OBJECTIVES_H

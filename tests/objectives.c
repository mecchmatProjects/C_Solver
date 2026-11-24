#include "objectives.h"
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <assert.h>

int input_check(const double x[],size_t n,void *ctx, size_t *expected_n) {
    if (ctx == NULL) {
        printf("ctx is NULL\n");
        return 0;
    }
    const size_t req_n = *(const size_t *)ctx;
    if (n != req_n) {
        printf("dimension mismatch (got n=%zu, expected %zu)\n",n,req_n);
        return 0;
    }
    if (n > 0 && x == NULL) {
        printf("input array x is NULL for n=%zu\n", n);
        return 0;
    }
    if (expected_n != NULL) {
        *expected_n = req_n;
    }
    return 1;
}

void fill_grad_nan(double g[], size_t n) {
    if (g == NULL) {
        return;
    }
    for (size_t i = 0; i < n; ++i) {
        g[i] = NAN;
    }
}

double miniai_test_quadratic(const double x[], size_t n, void *ctx) {
    size_t expected_n = 0;
    if (!input_check(x, n, ctx, &expected_n)) {
        return NAN;
    }
    double sum = 0.0;
    for (size_t i = 0; i < n; i++) {
        sum+=x[i]*x[i];
    }
    return sum;
}

void miniai_grad_quadratic(const double x[], double g[], size_t n, void *ctx) {
    size_t expected_n = 0;
    if (!input_check(x, n, ctx, &expected_n) || g == NULL) {
        fill_grad_nan(g, n);
        return;
    }
    for (size_t i = 0; i < n; ++i) {
        g[i] = 2.0 * x[i];
    }
}

double miniai_test_separable(const double x[], size_t n, void *ctx) {
    size_t expected_n = 0;
    if (!input_check(x, n, ctx, &expected_n)) {
        return NAN;
    }
    double sum = 0.0;
    for (size_t i = 0; i < n; ++i) {
        const double weight = (double)(i + 1);
        sum += weight * x[i] * x[i];
    }
    return sum;
}

void miniai_grad_separable(const double x[], double g[], size_t n, void *ctx) {
    size_t expected_n = 0;
    if (!input_check(x, n, ctx, &expected_n) || g == NULL) {
        fill_grad_nan(g, n);
        return;
    }
    for (size_t i = 0; i < n; ++i) {
        const double k = (double)(i + 1);
        g[i] = 2.0 * k * x[i];
    }
}

double miniai_test_bowl(const double x[], size_t n, void *ctx) {
    size_t expected_n = 0;
    if (!input_check(x, n, ctx, &expected_n)) {
        return NAN;
    }
    double sum = 0.0;
    for (size_t i = 0; i < n; ++i) {
        const double diff = x[i] - 1.0;
        sum += diff * diff;
    }
    return sum;
}

void miniai_grad_bowl(const double x[], double g[], size_t n, void *ctx) {
    size_t expected_n = 0;
    if (!input_check(x, n, ctx, &expected_n) || g == NULL) {
        fill_grad_nan(g, n);
        return;
    }
    for (size_t i = 0; i < n; ++i) {
        g[i] = 2.0 * (x[i] - 1.0);
    }
}

void objectives_test() {
    printf("starting tests\n");
    size_t n1 = 1;
    double x1[1] = {3.0};
    double g1[1] = {0.0};
    assert(fabs(miniai_test_quadratic(x1, n1, &n1) - 9.0)< 1e-12);
    miniai_grad_quadratic(x1, g1, n1, &n1);
    assert(fabs(g1[0] - 6.0) < 1e-12);
    assert(fabs(miniai_test_separable(x1, n1, &n1) - 9.0) < 1e-12);
    miniai_grad_separable(x1, g1, n1, &n1);
    assert(fabs(g1[0] - 6.0) < 1e-12);
    assert(fabs(miniai_test_bowl(x1, n1, &n1) - 4.0) < 1e-12);
    miniai_grad_bowl(x1, g1, n1, &n1);
    assert(fabs(g1[0] - 4.0)  < 1e-12);

    size_t n3 = 3;
    double x3[3] = {1.0, 2.0, 3.0};
    double g3[3] = {0.0, 0.0, 0.0};
    assert(fabs(miniai_test_quadratic(x3, n3, &n3) - 14.0)  < 1e-12);
    assert(fabs(miniai_test_separable(x3, n3, &n3) - 36.0) < 1e-12);
    assert(fabs(miniai_test_bowl(x3, n3, &n3) - 5.0) < 1e-12);

    miniai_grad_separable(x3, g3, n3, &n3);
    assert(fabs(g3[0] - 2.0) < 1e-12);
    assert(fabs(g3[1] - 8.0) < 1e-12);
    assert(fabs(g3[2] - 18.0) < 1e-12);


    assert(isnan(miniai_test_quadratic(x3, n3, NULL)) != 0);
    assert(isnan(miniai_test_quadratic(x3, 2, &n3))  != 0);
    assert(isnan(miniai_test_separable(x3, 2, &n3))  != 0);
    assert(isnan(miniai_test_bowl(x3, 2, &n3)) != 0);

    printf("test passed successfully\n");
}

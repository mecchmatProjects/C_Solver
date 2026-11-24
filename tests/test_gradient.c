#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "miniai/gradient.h"

#define ASSERT_NEAR(actual,expected) \
    do { \
        double a_ = (actual); \
        double e_ = (expected); \
        assert(isfinite(a_) && isfinite(e_) && \
               fabs(a_ - e_) <= 1e-12 + 1e-9 * fmax(fabs(a_), fabs(e_))); \
    } while (0)




static double quad2(const double x[], size_t n, void *context)
{
    size_t *calls = (size_t *)context;
    assert(n == 2);
    if (calls != NULL) {
        ++(*calls);
    }
    return x[0] * x[0] + 3.0 * x[1] * x[1];
}


static double sumsq(const double x[], size_t n, void *context)
{
    double s = 0.0;
    size_t i;
    size_t *calls = (size_t *)context;
    if (calls != NULL) {
        ++(*calls);
    }
    for (i = 0; i < n; ++i) {
        s += x[i] * x[i];
    }
    return s;
}

static double nan_objective(const double x[], size_t n, void *context)
{
    (void)x; (void)n; (void)context;
    return NAN;
}

static double inf_objective(const double x[], size_t n, void *context)
{
    (void)x; (void)n; (void)context;
    return INFINITY;
}



static void test_quadratic_known_gradient(void)
{
    double x[2] = {1.0, 2.0};
    double grad[2] = {0.0, 0.0};
    size_t calls = 0;
    int status = miniai_gradient_central(quad2, x, 2, 1e-5, &calls, grad);

    assert(status == MINIAI_GRADIENT_OK);
    ASSERT_NEAR(grad[0], 2.0);
    ASSERT_NEAR(grad[1], 12.0);

    assert(calls == 2u * 2u);
    puts("PASS test_quadratic_known_gradient");
}

static void test_exactly_2n_calls(void)
{
    double x[3] = {0.5, -1.5, 2.5};
    double grad[3] = {0.0, 0.0, 0.0};
    size_t calls = 0;
    int status = miniai_gradient_central(sumsq, x, 3, 1e-4, &calls, grad);

    assert(status == MINIAI_GRADIENT_OK);
    assert(calls == 6u);
    ASSERT_NEAR(grad[0], 1.0);
    ASSERT_NEAR(grad[1], -3.0);
    ASSERT_NEAR(grad[2], 5.0);
    puts("PASS test_exactly_2n_calls");
}

static void test_input_unchanged(void)
{
    double x[2] = {1.0, 2.0};
    double x_copy[2];
    double grad[2] = {0.0, 0.0};
    int status;

    memcpy(x_copy, x, sizeof(x));
    status = miniai_gradient_central(quad2, x, 2, 1e-5, NULL, grad);
    assert(status == MINIAI_GRADIENT_OK);
    assert(memcmp(x, x_copy, sizeof(x)) == 0);
    puts("PASS test_input_unchanged");
}

static void test_invalid_arguments(void)
{
    double x[2] = {1.0, 2.0};
    double grad[2] = {111.0, 222.0};
    double saved[2];
    int status;

    memcpy(saved, grad, sizeof(grad));

    status = miniai_gradient_central(NULL, x, 2, 1e-5, NULL, grad);
    assert(status == MINIAI_GRADIENT_INVALID_ARGUMENT);

    status = miniai_gradient_central(quad2, NULL, 2, 1e-5, NULL, grad);
    assert(status == MINIAI_GRADIENT_INVALID_ARGUMENT);

    status = miniai_gradient_central(quad2, x, 2, 1e-5, NULL, NULL);
    assert(status == MINIAI_GRADIENT_INVALID_ARGUMENT);

    status = miniai_gradient_central(quad2, x, 0, 1e-5, NULL, grad);
    assert(status == MINIAI_GRADIENT_INVALID_ARGUMENT);

    status = miniai_gradient_central(quad2, x, 2, 0.0, NULL, grad);
    assert(status == MINIAI_GRADIENT_INVALID_ARGUMENT);

    status = miniai_gradient_central(quad2, x, 2, -1e-5, NULL, grad);
    assert(status == MINIAI_GRADIENT_INVALID_ARGUMENT);

    status = miniai_gradient_central(quad2, x, 2, NAN, NULL, grad);
    assert(status == MINIAI_GRADIENT_INVALID_ARGUMENT);

    status = miniai_gradient_central(quad2, x, 2, INFINITY, NULL, grad);
    assert(status == MINIAI_GRADIENT_INVALID_ARGUMENT);


    {
        double bad[2] = {1.0, NAN};
        status = miniai_gradient_central(quad2, bad, 2, 1e-5, NULL, grad);
        assert(status == MINIAI_GRADIENT_INVALID_ARGUMENT);
    }


    assert(memcmp(grad, saved, sizeof(grad)) == 0);
    puts("PASS test_invalid_arguments");
}

static void test_nonfinite_objective(void)
{
    double x[2] = {1.0, 2.0};
    double grad[2] = {7.0, 7.0};
    double saved[2];
    int status;

    memcpy(saved, grad, sizeof(grad));
    status = miniai_gradient_central(nan_objective, x, 2, 1e-5, NULL, grad);
    assert(status == MINIAI_GRADIENT_NONFINITE_OBJECTIVE);
    assert(memcmp(grad, saved, sizeof(grad)) == 0);

    status = miniai_gradient_central(inf_objective, x, 2, 1e-5, NULL, grad);
    assert(status == MINIAI_GRADIENT_NONFINITE_OBJECTIVE);
    assert(memcmp(grad, saved, sizeof(grad)) == 0);
    puts("PASS test_nonfinite_objective");
}



static void test_central_beats_forward_accuracy(void)
{
    double x[2] = {1.0, 2.0};
    double grad_c[2] = {0.0, 0.0};
    double grad_f[2] = {0.0, 0.0};
    const double h = 1e-3;
    double f0 = quad2(x, 2, NULL);
    double f_plus;
    double f_minus;
    double tmp[2];
    double err_c;
    double err_f;

    assert(miniai_gradient_central(quad2, x, 2, h, NULL, grad_c) ==
           MINIAI_GRADIENT_OK);


    for (size_t i = 0; i < 2; ++i) {
        tmp[0] = x[0]; tmp[1] = x[1];
        tmp[i] += h;
        f_plus = quad2(tmp, 2, NULL);
        grad_f[i] = (f_plus - f0) / h;
        (void)f_minus;
    }

    err_c = fmax(fabs(grad_c[0] - 2.0), fabs(grad_c[1] - 12.0));
    err_f = fmax(fabs(grad_f[0] - 2.0), fabs(grad_f[1] - 12.0));
    assert(err_c < err_f);
    puts("PASS test_central_beats_forward_accuracy");
}

int main(void)
{
    test_quadratic_known_gradient();
    test_exactly_2n_calls();
    test_input_unchanged();
    test_invalid_arguments();
    test_nonfinite_objective();
    test_central_beats_forward_accuracy();
    puts("All B3 gradient tests passed.");
    return 0;
}

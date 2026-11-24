/* Lab 2 A9: tests for the Linear (identity) activation. */
#include <float.h>
#include <math.h>
#include <stdio.h>

#include "miniai/ml/activation/linear.h"

static int failures = 0;
static int checks = 0;

static int almost_equal(double a, double b, double abs_tol, double rel_tol) {
    if (!isfinite(a) || !isfinite(b)) {
        return 0;
    }
    return fabs(a - b) <= abs_tol + rel_tol * fmax(fabs(a), fabs(b));
}

static void expect_near(double actual, double expected, const char *message) {
    ++checks;
    if (!almost_equal(actual, expected, 1e-12, 1e-9)) {
        fprintf(stderr, "FAIL: %s (actual %.17g, expected %.17g)\n", message,
                actual, expected);
        ++failures;
    }
}

static void expect_exact(double actual, double expected, const char *message) {
    ++checks;
    if (actual != expected) {
        fprintf(stderr, "FAIL: %s (actual %.17g, expected %.17g)\n", message,
                actual, expected);
        ++failures;
    }
}

static void expect_true(int condition, const char *message) {
    ++checks;
    if (!condition) {
        fprintf(stderr, "FAIL: %s\n", message);
        ++failures;
    }
}

static void expect_status(ActivationStatus actual, ActivationStatus expected,
                          const char *message) {
    ++checks;
    if (actual != expected) {
        fprintf(stderr, "FAIL: %s (status %d, expected %d)\n", message,
                (int)actual, (int)expected);
        ++failures;
    }
}

static double value_at(const Activation *activation, double x) {
    double result = NAN;
    expect_status(activation_value(activation, x, &result),
                  ACTIVATION_STATUS_OK, "Linear value dispatch");
    return result;
}

static double derivative_at(const Activation *activation, double x) {
    double result = NAN;
    expect_status(activation_derivative(activation, x, &result),
                  ACTIVATION_STATUS_OK, "Linear derivative dispatch");
    return result;
}

static void test_init(Activation *activation) {
    expect_status(activation_linear_init(NULL),
                  ACTIVATION_STATUS_INVALID_ARGUMENT,
                  "reject NULL Linear initializer");
    expect_status(activation_linear_init(activation), ACTIVATION_STATUS_OK,
                  "initialize Linear");
    expect_true(activation->vtable != NULL &&
                    activation->vtable->value != NULL &&
                    activation->vtable->derivative != NULL,
                "Linear vtable has value and derivative callbacks");
}

static void test_basic_points(const Activation *activation) {
    const double xs[] = {-2.0, 0.0, 2.0};
    size_t i;

    for (i = 0; i < sizeof xs / sizeof xs[0]; ++i) {
        expect_near(value_at(activation, xs[i]), xs[i], "Linear f(x) = x");
        expect_exact(derivative_at(activation, xs[i]), 1.0,
                     "Linear f'(x) = 1");
    }
}

static void test_small_and_large_finite(const Activation *activation) {
    const double xs[] = {1e-300, -1e-300, DBL_MIN, DBL_TRUE_MIN,
                         1e300,  -1e300,  DBL_MAX, -DBL_MAX};
    size_t i;

    for (i = 0; i < sizeof xs / sizeof xs[0]; ++i) {
        /* Identity must return the exact input, without rounding. */
        expect_exact(value_at(activation, xs[i]), xs[i],
                     "Linear keeps small/large finite input exactly");
        expect_exact(derivative_at(activation, xs[i]), 1.0,
                     "Linear derivative is 1 for small/large finite input");
    }
}

static void test_signed_zero(const Activation *activation) {
    double value = value_at(activation, -0.0);

    expect_true(value == 0.0 && signbit(value),
                "Linear preserves negative zero: f(-0.0) == -0.0");
    expect_true(!signbit(value_at(activation, 0.0)),
                "Linear keeps positive zero positive");
    expect_exact(derivative_at(activation, -0.0), 1.0,
                 "Linear derivative at -0.0 is 1");
}

static void test_non_finite(const Activation *activation) {
    double pos_inf = value_at(activation, INFINITY);
    double neg_inf = value_at(activation, -INFINITY);

    expect_true(isinf(pos_inf) && pos_inf > 0.0, "Linear f(+Inf) = +Inf");
    expect_true(isinf(neg_inf) && neg_inf < 0.0, "Linear f(-Inf) = -Inf");
    expect_true(isnan(value_at(activation, NAN)), "Linear f(NaN) = NaN");
    expect_true(isnan(derivative_at(activation, INFINITY)),
                "Linear derivative at +Inf is not claimed (NAN)");
    expect_true(isnan(derivative_at(activation, -INFINITY)),
                "Linear derivative at -Inf is not claimed (NAN)");
    expect_true(isnan(derivative_at(activation, NAN)),
                "Linear derivative at NaN is NAN");
}

static void test_dispatch_validation(const Activation *activation) {
    double result = 123.0;

    expect_status(activation_value(activation, 1.0, NULL),
                  ACTIVATION_STATUS_INVALID_ARGUMENT,
                  "Linear value rejects NULL result");
    expect_status(activation_derivative(activation, 1.0, NULL),
                  ACTIVATION_STATUS_INVALID_ARGUMENT,
                  "Linear derivative rejects NULL result");
    expect_status(activation_value(NULL, 1.0, &result),
                  ACTIVATION_STATUS_INVALID_ARGUMENT,
                  "value dispatch rejects NULL activation");
    expect_exact(result, 123.0, "invalid call does not overwrite result");
}

int main(void) {
    Activation activation;

    test_init(&activation);
    test_basic_points(&activation);
    test_small_and_large_finite(&activation);
    test_signed_zero(&activation);
    test_non_finite(&activation);
    test_dispatch_validation(&activation);

    if (failures != 0) {
        fprintf(stderr, "%d of %d Linear checks failed\n", failures, checks);
        return 1;
    }

    printf("%d Linear checks passed\n", checks);
    return 0;
}

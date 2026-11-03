#include <math.h>
#include <stdio.h>

#include "miniai/ml/activation/invsqrt.h"

static int failures = 0;
static int checks = 0;

static void expect_near(double actual, double expected, const char *message) {
    ++checks;
    if (!(fabs(actual - expected) <= 1e-12)) {
        fprintf(stderr, "FAIL: %s (actual %.17g, expected %.17g)\n", message,
                actual, expected);
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

static void expect_positive(double actual, const char *message) {
    ++checks;
    if (!(actual > 0.0)) {
        fprintf(stderr, "FAIL: %s (actual %.17g)\n", message, actual);
        ++failures;
    }
}

static void test_invsqrt_identity(void) {
    Activation activation;
    double value = 0.0;
    double derivative = 0.0;
    const double points[] = {-1.0, 0.0, 1.0};
    size_t index;

    expect_status(activation_invsqrt_init(&activation, 0.0),
                  ACTIVATION_STATUS_OK, "initialize InvSqrt with alpha zero");
    for (index = 0; index < 3; ++index) {
        expect_status(activation_value(&activation, points[index], &value),
                      ACTIVATION_STATUS_OK, "evaluate identity InvSqrt");
        expect_near(value, points[index], "InvSqrt alpha zero value");
        expect_status(activation_derivative(&activation, points[index],
                                            &derivative),
                      ACTIVATION_STATUS_OK, "differentiate identity InvSqrt");
        expect_near(derivative, 1.0, "InvSqrt alpha zero derivative");
    }
}

static void test_invsqrt_unit_alpha(void) {
    Activation activation;
    double value = 0.0;
    double derivative = 0.0;
    const double inv_sqrt2 = 1.0 / sqrt(2.0);
    const double deriv_one = 1.0 / (2.0 * sqrt(2.0));

    expect_status(activation_invsqrt_init(&activation, 1.0),
                  ACTIVATION_STATUS_OK, "initialize InvSqrt with alpha one");

    expect_status(activation_value(&activation, 0.0, &value),
                  ACTIVATION_STATUS_OK, "evaluate InvSqrt at zero");
    expect_near(value, 0.0, "InvSqrt value at zero");
    expect_status(activation_value(&activation, 1.0, &value),
                  ACTIVATION_STATUS_OK, "evaluate InvSqrt at one");
    expect_near(value, inv_sqrt2, "InvSqrt value at one");
    expect_status(activation_value(&activation, -1.0, &value),
                  ACTIVATION_STATUS_OK, "evaluate InvSqrt at minus one");
    expect_near(value, -inv_sqrt2, "InvSqrt value at minus one");

    expect_status(activation_derivative(&activation, 0.0, &derivative),
                  ACTIVATION_STATUS_OK, "differentiate InvSqrt at zero");
    expect_near(derivative, 1.0, "InvSqrt derivative at zero");
    expect_status(activation_derivative(&activation, 1.0, &derivative),
                  ACTIVATION_STATUS_OK, "differentiate InvSqrt at one");
    expect_near(derivative, deriv_one, "InvSqrt derivative at one");
    expect_status(activation_derivative(&activation, -1.0, &derivative),
                  ACTIVATION_STATUS_OK, "differentiate InvSqrt at minus one");
    expect_near(derivative, deriv_one, "InvSqrt derivative is even");
}

static void test_invsqrt_large_input(void) {
    Activation activation;
    double value = 0.0;
    double derivative = 1.0;

    expect_status(activation_invsqrt_init(&activation, 4.0),
                  ACTIVATION_STATUS_OK, "initialize InvSqrt with alpha four");
    expect_status(activation_value(&activation, 1e200, &value),
                  ACTIVATION_STATUS_OK, "evaluate InvSqrt at huge input");
    expect_near(value, 0.5, "InvSqrt saturates at 1/sqrt(alpha)");
    expect_status(activation_derivative(&activation, 1e200, &derivative),
                  ACTIVATION_STATUS_OK, "differentiate InvSqrt at huge input");
    expect_near(derivative, 0.0, "InvSqrt derivative vanishes at huge input");
    expect_status(activation_value(&activation, -1e200, &value),
                  ACTIVATION_STATUS_OK, "evaluate InvSqrt at huge negative");
    expect_near(value, -0.5, "InvSqrt saturates at minus 1/sqrt(alpha)");
}

static void test_invsqrt_range_limit(void) {
    Activation activation;
    double value = 0.0;
    double derivative = 0.0;

    expect_status(activation_invsqrt_init(&activation, 4.0),
                  ACTIVATION_STATUS_OK, "initialize InvSqrt near range limit");
    expect_status(activation_value(&activation, 1e308, &value),
                  ACTIVATION_STATUS_OK, "evaluate InvSqrt at 1e308");
    expect_near(value, 0.5, "InvSqrt value at 1e308 does not overflow");
    expect_status(activation_value(&activation, -1e308, &value),
                  ACTIVATION_STATUS_OK, "evaluate InvSqrt at -1e308");
    expect_near(value, -0.5, "InvSqrt value at -1e308 does not overflow");

    expect_status(activation_invsqrt_init(&activation, 1.0),
                  ACTIVATION_STATUS_OK, "initialize InvSqrt with alpha one");
    expect_status(activation_derivative(&activation, 1e103, &derivative),
                  ACTIVATION_STATUS_OK, "differentiate InvSqrt at 1e103");
    expect_positive(derivative, "InvSqrt derivative at 1e103 is not lost");
}

static void test_invsqrt_validation(void) {
    Activation activation;

    expect_status(activation_invsqrt_init(NULL, 1.0),
                  ACTIVATION_STATUS_INVALID_ARGUMENT,
                  "reject null InvSqrt initializer");
    expect_status(activation_invsqrt_init(&activation, -1.0),
                  ACTIVATION_STATUS_INVALID_ARGUMENT,
                  "reject negative InvSqrt alpha");
    expect_status(activation_invsqrt_init(&activation, NAN),
                  ACTIVATION_STATUS_INVALID_ARGUMENT,
                  "reject NaN InvSqrt alpha");
    expect_status(activation_invsqrt_init(&activation, INFINITY),
                  ACTIVATION_STATUS_INVALID_ARGUMENT,
                  "reject infinite InvSqrt alpha");
    expect_status(activation_invsqrt_init(&activation, -INFINITY),
                  ACTIVATION_STATUS_INVALID_ARGUMENT,
                  "reject negative infinite InvSqrt alpha");
}

int main(void) {
    test_invsqrt_identity();
    test_invsqrt_unit_alpha();
    test_invsqrt_large_input();
    test_invsqrt_range_limit();
    test_invsqrt_validation();

    if (failures != 0) {
        fprintf(stderr, "%d of %d InvSqrt checks failed\n", failures, checks);
        return 1;
    }

    printf("%d InvSqrt checks passed\n", checks);
    return 0;
}

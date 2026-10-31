#include <math.h>
#include <stdio.h>

#include "miniai/ml/activation/sigmoid.h"
#include "miniai/ml/loss/losses.h"

static int checks;
static int failures;

static void expect_near(double actual, double expected, const char *message) {
    ++checks;
    if (!isfinite(actual) || fabs(actual - expected) > 1e-12) {
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

static void expect_nan(double actual, const char *message) {
    ++checks;
    if (!isnan(actual)) {
        fprintf(stderr, "FAIL: %s (actual %.17g, expected NAN)\n", message,
                actual);
        ++failures;
    }
}

int run_loss_tests(void) {
    const double prediction = 1.25;
    const double target = 0.5;
    const double delta = 0.4;
    Activation sigmoid = {0};
    double probability = NAN;

    checks = 0;
    failures = 0;

    expect_near(miniai_squared_error(prediction, target),
                miniai_squared_error(target, prediction),
                "squared error is symmetric");
    expect_near(miniai_squared_error(target, target), 0.0,
                "squared error is zero for equal inputs");
    expect_true(miniai_squared_error_derivative(prediction, target) > 0.0,
                "squared error derivative is positive above target");
    expect_true(miniai_squared_error_derivative(target, prediction) < 0.0,
                "squared error derivative is negative below target");

    expect_near(miniai_absolute_error(prediction, target),
                miniai_absolute_error(target, prediction),
                "absolute error is symmetric");
    expect_near(miniai_absolute_error(target, target), 0.0,
                "absolute error is zero for equal inputs");
    expect_true(miniai_absolute_error_derivative(prediction, target) > 0.0,
                "absolute error subgradient is positive above target");
    expect_true(miniai_absolute_error_derivative(target, prediction) < 0.0,
                "absolute error subgradient is negative below target");

    expect_near(miniai_huber_loss(prediction, target, delta),
                miniai_huber_loss(target, prediction, delta),
                "Huber loss is symmetric");
    expect_near(miniai_huber_loss(target, target, delta), 0.0,
                "Huber loss is zero for equal inputs");
    expect_true(miniai_huber_loss_derivative(prediction, target, delta) > 0.0,
                "Huber derivative is positive above target");
    expect_true(miniai_huber_loss_derivative(target, prediction, delta) < 0.0,
                "Huber derivative is negative below target");

    expect_near(miniai_log_cosh_loss(prediction, target),
                miniai_log_cosh_loss(target, prediction),
                "log-cosh loss is symmetric");
    expect_near(miniai_log_cosh_loss(target, target), 0.0,
                "log-cosh loss is zero for equal inputs");
    expect_true(miniai_log_cosh_loss_derivative(prediction, target) > 0.0,
                "log-cosh derivative is positive above target");
    expect_true(miniai_log_cosh_loss_derivative(target, prediction) < 0.0,
                "log-cosh derivative is negative below target");

    expect_nan(miniai_binary_cross_entropy(-0.1, 0.5),
               "BCE rejects a prediction outside [0,1]");
    expect_nan(miniai_binary_cross_entropy_derivative(0.5, 1.1),
               "BCE derivative rejects a target outside [0,1]");
    expect_nan(miniai_huber_loss(prediction, target, 0.0),
               "Huber loss rejects zero delta");
    expect_nan(miniai_log_cosh_loss_derivative(NAN, target),
               "log-cosh derivative rejects NaN input");

    expect_true(activation_sigmoid_init(&sigmoid) == ACTIVATION_STATUS_OK,
                "initialize sigmoid for scalar loss pipeline");
    expect_true(activation_value(&sigmoid, 0.0, &probability) ==
                    ACTIVATION_STATUS_OK,
                "evaluate sigmoid for scalar loss pipeline");
    expect_near(probability, 0.5, "sigmoid pipeline produces expected probability");
    expect_near(miniai_squared_error(probability, 1.0), 0.25,
                "sigmoid output feeds squared error");

    printf("Loss integration checks: %d, failures: %d\n", checks, failures);
    return failures == 0 ? 0 : 1;
}

int main(void) {
    return run_loss_tests();
}
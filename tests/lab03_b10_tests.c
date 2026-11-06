#include <math.h>
#include <stdio.h>

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

static void expect_nan(double actual, const char *message) {
    ++checks;
    if (!isnan(actual)) {
        fprintf(stderr, "FAIL: %s (actual %.17g, expected NAN)\n", message,
                actual);
        ++failures;
    }
}

int main(void) {
    const double pred[] = {1.0, 2.0};
    const double target[] = {0.0, 2.0};
    const double equal[] = {-2.0, 0.0, 3.0};
    const double singleton_pred[] = {4.0};
    const double singleton_target[] = {1.0};
    const double negative_pred[] = {-1.0, -3.0};
    const double negative_target[] = {-2.0, -1.0};
    const double nonfinite_pred[] = {0.0, NAN};
    const double finite_target[] = {0.0, 1.0};
    const double infinite_target[] = {0.0, INFINITY};
    const double large_pred[] = {1e308};
    const double large_target[] = {-1e308};

    expect_near(miniai_mse(pred, target, 2), 0.5,
                "[1,2] vs [0,2] has MSE 0.5");
    expect_near(miniai_mse(equal, equal, 3), 0.0,
                "equal vectors have zero MSE");
    expect_near(miniai_mse(singleton_pred, singleton_target, 1), 9.0,
                "singleton vectors have squared error as MSE");
    expect_near(miniai_mse(negative_pred, negative_target, 2), 2.5,
                "MSE handles negative values");
    expect_near(miniai_mse(target, pred, 2), 0.5,
                "swapping vectors preserves MSE");

    expect_nan(miniai_mse(NULL, NULL, 0), "empty input returns NAN");
    expect_nan(miniai_mse(NULL, target, 2), "NULL prediction returns NAN");
    expect_nan(miniai_mse(pred, NULL, 2), "NULL target returns NAN");
    expect_nan(miniai_mse(nonfinite_pred, finite_target, 2),
               "NaN input element returns NAN");
    expect_nan(miniai_mse(pred, infinite_target, 2),
               "infinite input element returns NAN");
    expect_nan(miniai_mse(large_pred, large_target, 1),
               "non-finite scalar squared error returns NAN");

    if (failures != 0) {
        fprintf(stderr, "%d of %d Lab 3 B10 checks failed\n", failures,
                checks);
        return 1;
    }

    printf("%d Lab 3 B10 checks passed\n", checks);
    return 0;
}

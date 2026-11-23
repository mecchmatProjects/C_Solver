#include <math.h>
#include <stdio.h>

#include "miniai/ml/loss/losses.h"

static int failures = 0;
static int checks = 0;

static int almost_equal(double a, double b, double abs_tol, double rel_tol) {
    if (!isfinite(a) || !isfinite(b)) return 0;
    return fabs(a - b) <= abs_tol + rel_tol * fmax(fabs(a), fabs(b));
}

static void expect_nan(double actual, const char *message) {
    ++checks;
    if (!isnan(actual)) {
        fprintf(stderr, "FAIL: %s (expected NAN, got %.17g)\n", message, actual);
        ++failures;
    }
}

static void expect_near(double actual, double expected, const char *message) {
    ++checks;
    if (!almost_equal(actual, expected, 1e-12, 1e-9)) {
        fprintf(stderr, "FAIL: %s (actual %.17g, expected %.17g)\n", message, actual, expected);
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

static void test_absolute_error_domain(void) {
    expect_nan(miniai_absolute_error(NAN, 1.0), "absolute_error: NaN prediction");
    expect_nan(miniai_absolute_error(1.0, NAN), "absolute_error: NaN target");
    expect_nan(miniai_absolute_error(INFINITY, 1.0), "absolute_error: +Inf prediction");
    expect_nan(miniai_absolute_error(1.0, -INFINITY), "absolute_error: -Inf target");
}

static void test_absolute_error_derivative_domain(void) {
    expect_nan(miniai_absolute_error_derivative(NAN, 0.0), "absolute_error_derivative: NaN prediction");
    expect_nan(miniai_absolute_error_derivative(0.0, INFINITY), "absolute_error_derivative: Inf target");
    expect_near(miniai_absolute_error_derivative(2.0, 2.0), 0.0, "absolute_error_derivative: subgradient 0 at p == y");
    expect_near(miniai_absolute_error_derivative(-0.0, 0.0), 0.0, "absolute_error_derivative: -0.0 == 0.0");
}

static void test_bce_derivative_domain(void) {
    expect_nan(miniai_binary_cross_entropy_derivative(NAN, 1.0), "bce_derivative: NaN prediction");
    expect_nan(miniai_binary_cross_entropy_derivative(INFINITY, 1.0), "bce_derivative: Inf prediction");
    expect_nan(miniai_binary_cross_entropy_derivative(0.5, NAN), "bce_derivative: NaN target");
    expect_nan(miniai_binary_cross_entropy_derivative(0.5, -0.1), "bce_derivative: target < 0");
    expect_nan(miniai_binary_cross_entropy_derivative(0.5, 1.1), "bce_derivative: target > 1");
}

static void test_bce_derivative_clipping(void) {
    double eps = 1e-12;
    double left = miniai_binary_cross_entropy_derivative(0.0, 1.0);
    double right = miniai_binary_cross_entropy_derivative(1.0, 0.0);

    expect_true(isfinite(left) && left < 0.0, "bce_derivative: p = 0 is clipped, finite and negative");
    expect_true(isfinite(right) && right > 0.0, "bce_derivative: p = 1 is clipped, finite and positive");
    expect_near(left, -1.0 / eps, "bce_derivative: value at clipped p_c = eps");
    expect_near(miniai_binary_cross_entropy_derivative(0.5, 0.25), 1.0, "bce_derivative: soft label y = 0.25");
}

int main(void) {
    test_absolute_error_domain();
    test_absolute_error_derivative_domain();
    test_bce_derivative_domain();
    test_bce_derivative_clipping();

    printf("loss contract tests: %d checks, %d failures\n", checks, failures);
    return failures != 0;
}

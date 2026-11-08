#include <math.h>
#include <stdio.h>

#include "miniai/ml/loss/losses.h"

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

static void expect_nan(double actual, const char *message) {
    ++checks;
    if (!isnan(actual)) {
        fprintf(stderr, "FAIL: %s (actual %.17g, expected NAN)\n", message,
                actual);
        ++failures;
    }
}

static void test_huber_values(void) {
    const double delta = 2.0;

    expect_near(miniai_huber_loss(3.0, 3.0, delta), 0.0,
                "zero error has zero Huber loss");
    expect_near(miniai_huber_loss(1.0, 0.0, delta), 0.5,
                "quadratic region uses half squared error");
    expect_near(miniai_huber_loss(1.0, 0.0, 2.0), 0.5,
                "assignment example e=0.5 delta");
    expect_near(miniai_huber_loss(4.0, 0.0, delta), 6.0,
                "assignment example e=2 delta");
    expect_near(miniai_huber_loss(-4.0, 0.0, delta), 6.0,
                "Huber loss is symmetric for negative residual");
}

static void test_transition_boundaries(void) {
    const double delta = 1.5;
    const double expected = 0.5 * delta * delta;

    expect_near(miniai_huber_loss(delta, 0.0, delta), expected,
                "positive delta boundary uses quadratic value");
    expect_near(miniai_huber_loss(-delta, 0.0, delta), expected,
                "negative delta boundary uses quadratic value");
    expect_near(miniai_huber_loss(delta + 0.5, 0.0, delta),
                delta * ((delta + 0.5) - 0.5 * delta),
                "value just above boundary uses linear tail");
}

static void test_invalid_inputs(void) {
    expect_nan(miniai_huber_loss(1.0, 0.0, 0.0), "reject zero delta");
    expect_nan(miniai_huber_loss(1.0, 0.0, -1.0), "reject negative delta");
    expect_nan(miniai_huber_loss(1.0, 0.0, NAN), "reject NaN delta");
    expect_nan(miniai_huber_loss(1.0, 0.0, INFINITY),
               "reject infinite delta");
    expect_nan(miniai_huber_loss(NAN, 0.0, 1.0), "reject NaN prediction");
    expect_nan(miniai_huber_loss(1.0, INFINITY, 1.0),
               "reject infinite target");
}

int main(void) {
    test_huber_values();
    test_transition_boundaries();
    test_invalid_inputs();

    if (failures != 0) {
        fprintf(stderr, "%d of %d Lab 2 B8 checks failed\n", failures, checks);
        return 1;
    }

    printf("%d Lab 2 B8 checks passed\n", checks);
    return 0;
}
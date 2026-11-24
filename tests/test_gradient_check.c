#include <math.h>
#include <stdio.h>

#include "miniai/gradient_check.h"

static int failures = 0;
static int checks = 0;

static void expect_near(double actual, double expected, const char *name) {
    ++checks;
    if (isnan(expected) ? !isnan(actual)
                        : isinf(expected)
                              ? actual != expected
                              : !isfinite(actual) ||
                                    fabs(actual - expected) > 1e-12) {
        fprintf(stderr, "FAIL: %s (actual %.17g, expected %.17g)\n", name,
                actual, expected);
        ++failures;
    }
}

static void test_known_errors(void) {
    const double exact[] = {100.0, 1.0, 0.0};
    const double approx[] = {110.0, 2.0, 1.0};

    expect_near(miniai_gradient_max_abs_error(exact, approx, 3), 10.0,
                "known maximum absolute error");
    expect_near(miniai_gradient_max_rel_error(exact, approx, 3, 0.5), 2.0,
                "known maximum relative error");
}

static void test_equal_vectors_and_floor(void) {
    const double exact[] = {0.0, -4.0};
    const double same[] = {0.0, -4.0};
    const double approx[] = {0.1, -4.0};

    expect_near(miniai_gradient_max_abs_error(exact, same, 2), 0.0,
                "equal vectors have zero absolute error");
    expect_near(miniai_gradient_max_rel_error(exact, same, 2, 0.5), 0.0,
                "equal vectors have zero relative error");
    expect_near(miniai_gradient_max_rel_error(exact, approx, 2, 0.5), 0.2,
                "floor is used for zero exact component");
}

static void test_empty_and_null_inputs(void) {
    const double value[] = {1.0};

    expect_near(miniai_gradient_max_abs_error(value, value, 0), NAN,
                "absolute error rejects empty vectors");
    expect_near(miniai_gradient_max_rel_error(value, value, 0, 1.0), NAN,
                "relative error rejects empty vectors");
    expect_near(miniai_gradient_max_abs_error(NULL, value, 1), NAN,
                "absolute error rejects NULL exact vector");
    expect_near(miniai_gradient_max_rel_error(value, NULL, 1, 1.0), NAN,
                "relative error rejects NULL approximate vector");
}

static void test_invalid_floor_and_non_finite_elements(void) {
    const double value[] = {1.0};
    const double not_finite[] = {INFINITY};

    expect_near(miniai_gradient_max_rel_error(value, value, 1, 0.0), NAN,
                "relative error rejects zero floor");
    expect_near(miniai_gradient_max_rel_error(value, value, 1, -1.0), NAN,
                "relative error rejects negative floor");
    expect_near(miniai_gradient_max_rel_error(value, value, 1, NAN), NAN,
                "relative error rejects non-finite floor");
    expect_near(miniai_gradient_max_abs_error(not_finite, value, 1), NAN,
                "absolute error rejects non-finite elements");
    expect_near(miniai_gradient_max_rel_error(value, not_finite, 1, 1.0), NAN,
                "relative error rejects non-finite elements");
}

int main(void) {
    test_known_errors();
    test_equal_vectors_and_floor();
    test_empty_and_null_inputs();
    test_invalid_floor_and_non_finite_elements();

    if (failures != 0) {
        fprintf(stderr, "%d of %d gradient-check tests failed\n", failures,
                checks);
        return 1;
    }
    printf("All %d gradient-check tests passed\n", checks);
    return 0;
}

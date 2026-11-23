#include <math.h>
#include <stdio.h>

#include "miniai/math/vector.h"

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

static void expect_zero(int actual, const char *message) {
    ++checks;
    if (actual != 0) {
        fprintf(stderr, "FAIL: %s (code %d, expected 0)\n", message, actual);
        ++failures;
    }
}

static void expect_nonzero(int actual, const char *message) {
    ++checks;
    if (actual == 0) {
        fprintf(stderr, "FAIL: %s (code 0, expected non-zero)\n", message);
        ++failures;
    }
}

static void test_basic(void) {
    const double a[] = {3.0, 4.0};
    const double b[] = {1.0, 2.0};
    double out[2] = {0.0, 0.0};

    expect_zero(miniai_vector_subtract(a, b, out, 2), "subtract two vectors");
    expect_near(out[0], 2.0, "first component of [3,4]-[1,2]");
    expect_near(out[1], 2.0, "second component of [3,4]-[1,2]");
}

static void test_single_element(void) {
    const double a[] = {5.5};
    const double b[] = {0.5};
    double out[1] = {0.0};

    expect_zero(miniai_vector_subtract(a, b, out, 1), "subtract one element");
    expect_near(out[0], 5.0, "single element difference");
}

static void test_negatives(void) {
    const double a[] = {-1.0, -2.0, 0.0};
    const double b[] = {3.0, -4.0, -0.5};
    double out[3] = {0.0, 0.0, 0.0};

    expect_zero(miniai_vector_subtract(a, b, out, 3),
                "subtract vectors with negatives");
    expect_near(out[0], -4.0, "negative minus positive");
    expect_near(out[1], 2.0, "negative minus negative");
    expect_near(out[2], 0.5, "zero minus negative");
}

static void test_in_place(void) {
    double a[] = {3.0, 4.0, 5.0};
    double b[] = {1.0, 2.0, 3.0};

    expect_zero(miniai_vector_subtract(a, b, a, 3), "subtract into first input");
    expect_near(a[0], 2.0, "in-place first component");
    expect_near(a[1], 2.0, "in-place second component");
    expect_near(a[2], 2.0, "in-place third component");

    expect_zero(miniai_vector_subtract(a, b, b, 3),
                "subtract into second input");
    expect_near(b[0], 1.0, "in-place second operand first component");
    expect_near(b[2], -1.0, "in-place second operand third component");
}

static void test_empty(void) {
    double out[1] = {42.0};

    expect_zero(miniai_vector_subtract(NULL, NULL, NULL, 0),
                "accept empty vectors");
    expect_zero(miniai_vector_subtract(out, out, out, 0),
                "accept empty vectors with valid pointers");
    expect_near(out[0], 42.0, "empty subtraction leaves output unchanged");
}

static void test_null_arguments(void) {
    const double a[] = {1.0, 2.0};
    const double b[] = {3.0, 4.0};
    double out[2] = {42.0, 42.0};

    expect_nonzero(miniai_vector_subtract(NULL, b, out, 2), "reject NULL a");
    expect_nonzero(miniai_vector_subtract(a, NULL, out, 2), "reject NULL b");
    expect_nonzero(miniai_vector_subtract(a, b, NULL, 2), "reject NULL out");
    expect_near(out[0], 42.0, "failed call leaves output unchanged");
    expect_near(out[1], 42.0, "failed call leaves output unchanged at end");
}

int main(void) {
    test_basic();
    test_single_element();
    test_negatives();
    test_in_place();
    test_empty();
    test_null_arguments();

    if (failures != 0) {
        fprintf(stderr, "%d of %d vector subtraction checks failed\n", failures,
                checks);
        return 1;
    }

    printf("%d vector subtraction checks passed\n", checks);
    return 0;
}

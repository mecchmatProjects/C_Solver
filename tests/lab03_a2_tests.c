//
// Created by Katya on 06.11.2026.
//
#include <math.h>
#include <stdio.h>

#include "miniai/math/vector.h"

static int failures;
static int checks;

static void expect(int condition, const char *message) {
    ++checks;
    if (!condition) {
        fprintf(stderr, "FAIL: %s\n", message);
        ++failures;
    }
}

static int almost_equal(double actual, double expected) {
    if (!isfinite(actual) || !isfinite(expected)) {
        return 0;
    }

    return fabs(actual - expected) <=
           1e-12 + 1e-9 * fmax(fabs(actual), fabs(expected));
}

static void test_addition(void) {
    const double a[] = {1.0, 2.0};
    const double b[] = {3.0, 4.0};
    const double single_a[] = {-2.5};
    const double single_b[] = {1.0};
    double out[2] = {0.0, 0.0};

    expect(miniai_vector_add(a, b, out, 2) == 0 &&
           almost_equal(out[0], 4.0) && almost_equal(out[1], 6.0),
           "[1, 2] + [3, 4] = [4, 6]");

    expect(miniai_vector_add(single_a, single_b, out, 1) == 0 &&
           almost_equal(out[0], -1.5),
           "single-element addition");
}

static void test_in_place(void) {
    double a[] = {1.0, 2.0};
    double b[] = {3.0, 4.0};

    expect(miniai_vector_add(a, b, a, 2) == 0 &&
           almost_equal(a[0], 4.0) && almost_equal(a[1], 6.0),
           "output can be the first input");

    expect(miniai_vector_add(a, b, b, 2) == 0 &&
           almost_equal(b[0], 7.0) && almost_equal(b[1], 10.0),
           "output can be the second input");
}

static void test_empty_and_null(void) {
    const double a[] = {1.0, 2.0};
    const double b[] = {3.0, 4.0};
    double out[] = {42.0, 43.0};

    expect(miniai_vector_add(NULL, NULL, NULL, 0) == 0,
           "empty input accepts NULL pointers");

    expect(miniai_vector_add(a, b, out, 0) == 0 &&
           almost_equal(out[0], 42.0) && almost_equal(out[1], 43.0),
           "empty input leaves output unchanged");

    expect(miniai_vector_add(NULL, b, out, 2) != 0, "reject NULL a");
    expect(miniai_vector_add(a, NULL, out, 2) != 0, "reject NULL b");
    expect(miniai_vector_add(a, b, NULL, 2) != 0, "reject NULL out");

    expect(almost_equal(out[0], 42.0) && almost_equal(out[1], 43.0),
           "invalid input leaves output unchanged");
}

int main(void) {
    test_addition();
    test_in_place();
    test_empty_and_null();

    if (failures != 0) {
        fprintf(stderr, "%d of %d checks failed\n", failures, checks);
        return 1;
    }

    printf("%d vector addition checks passed\n", checks);
    return 0;
}
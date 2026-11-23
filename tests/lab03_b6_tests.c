#include "miniai/math/statistics.h"

#include <math.h>
#include <stdio.h>

static int failures = 0;
static int checks = 0;

static void expect_near(double actual, double expected,
                        const char *message)
{
    ++checks;
    if (!(fabs(actual - expected) <= 1e-12)) {
        fprintf(stderr, "FAIL: %s (actual %.17g, expected %.17g)\n",
                message, actual, expected);
        ++failures;
    }
}

static void expect_zero(int actual, const char *message)
{
    ++checks;
    if (actual != 0) {
        fprintf(stderr, "FAIL: %s (code %d, expected 0)\n",
                message, actual);
        ++failures;
    }
}

static void expect_nonzero(int actual, const char *message)
{
    ++checks;
    if (actual == 0) {
        fprintf(stderr, "FAIL: %s (code 0, expected non-zero)\n",
                message);
        ++failures;
    }
}

static void expect_true(int condition, const char *message)
{
    ++checks;
    if (!condition) {
        fprintf(stderr, "FAIL: %s\n", message);
        ++failures;
    }
}

static void test_mandatory(void)
{
    const double in[] = {0.0, 5.0, 10.0};
    double out[3];

    expect_zero(miniai_minmax_scale(in, out, 3),
                "mandatory scaling");
    expect_near(out[0], 0.0, "first value");
    expect_near(out[1], 0.5, "middle value");
    expect_near(out[2], 1.0, "last value");
}

static void test_in_place(void)
{
    double values[] = {-10.0, 0.0, 10.0};

    expect_zero(miniai_minmax_scale(values, values, 3),
                "in-place scaling");
    expect_near(values[0], 0.0, "in-place minimum");
    expect_near(values[1], 0.5, "in-place middle");
    expect_near(values[2], 1.0, "in-place maximum");
}

static void test_empty(void)
{
    double out[] = {42.0};

    expect_nonzero(miniai_minmax_scale(NULL, NULL, 0),
                   "reject n == 0");
    expect_nonzero(miniai_minmax_scale(out, out, 0),
                   "reject n == 0 with non-NULL pointers");
}

static void test_null_arguments(void)
{
    const double in[] = {1.0, 2.0};
    double out[] = {42.0, 42.0};

    expect_nonzero(miniai_minmax_scale(NULL, out, 2),
                   "reject NULL input");
    expect_nonzero(miniai_minmax_scale(in, NULL, 2),
                   "reject NULL output");
    expect_near(out[0], 42.0, "failed call leaves first output unchanged");
    expect_near(out[1], 42.0, "failed call leaves second output unchanged");
}

static void test_constant_array(void)
{
    const double in[] = {7.0, 7.0, 7.0};
    double out[] = {1.0, 2.0, 3.0};

    expect_nonzero(miniai_minmax_scale(in, out, 3),
                   "reject constant array");
    expect_near(out[0], 1.0, "constant failure leaves first output unchanged");
    expect_near(out[1], 2.0, "constant failure leaves second output unchanged");
    expect_near(out[2], 3.0, "constant failure leaves third output unchanged");
}

static void test_nonfinite(void)
{
    const double in[] = {0.0, NAN, 1.0};
    double out[] = {1.0, 2.0, 3.0};

    expect_nonzero(miniai_minmax_scale(in, out, 3),
                   "reject non-finite input");
    expect_near(out[0], 1.0, "non-finite failure leaves output unchanged");
    expect_near(out[1], 2.0, "non-finite failure leaves output unchanged");
    expect_near(out[2], 3.0, "non-finite failure leaves output unchanged");
}

static void test_min_and_max_dependencies(void)
{
    const double in[] = {-3.0, 0.0, 8.0};

    expect_near(miniai_min(in, 3), -3.0, "minimum dependency");
    expect_near(miniai_max(in, 3), 8.0, "maximum dependency");
    expect_true(isnan(miniai_min(NULL, 0)), "minimum rejects empty input");
    expect_true(isnan(miniai_max(NULL, 0)), "maximum rejects empty input");
}

int main(void)
{
    test_mandatory();
    test_in_place();
    test_empty();
    test_null_arguments();
    test_constant_array();
    test_nonfinite();
    test_min_and_max_dependencies();

    if (failures != 0) {
        fprintf(stderr, "%d of %d checks failed\n", failures, checks);
        return 1;
    }

    printf("%d checks passed\n", checks);
    return 0;
}

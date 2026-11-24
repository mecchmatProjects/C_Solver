#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include "../src/gradient_safe.c"


static int failures = 0;
static int checks = 0;

static void expect_near(double actual, double expected, const char *message) {
    ++checks;
    if (isnan(expected) ? !isnan(actual)
                        : !(fabs(actual - expected) <= 1e-4)) {
        fprintf(stderr, "FAIL: %s (actual %.17g, expected %.17g)\n", message,
                actual, expected);
        ++failures;
                        }
}

static void expect_status(double actual, double expected,
                          const char *message) {
    ++checks;
    if (actual != expected) {
        fprintf(stderr, "FAIL: %s (status %d, expected %d)\n", message,
                (int)actual, (int)expected);
        ++failures;
    }
}

static double f_valid(const double x[], size_t n, void* context) {
    (void) context;
    double sum = 0.0;
    for (size_t i = 0; i < n; i++) {
        sum = sum + x[i] * x[i];
    }
    return sum;
}

static double f_fail(const double x[], size_t n, void* context) {
    (void) context;
    if (n > 1 && x[1] > 2.00005) {
        return NAN;
    }
    return x[0] + x[1];
}

static void test_gradient_errors(void) {
    double x[] = {1.0, 2.0};
    double grad[] = {99.0, 99.0};

    expect_status(miniai_gradient_forward_safe(NULL, x, 2, 1e-5, NULL, grad), -1, "null f");
    expect_near(grad[0], 99.0, "grad unchanged 1");

    size_t big_n = (SIZE_MAX / sizeof(double)) + 1;
    expect_status(miniai_gradient_forward_safe(f_valid, x, big_n, 1e-5, NULL, grad), -2, "n overflow");
    expect_near(grad[0], 99.0, "grad unchanged 2");

    expect_status(miniai_gradient_forward_safe(f_fail, x, 2, 1e-4, NULL, grad), -4, "midway fail");
    expect_near(grad[0], 99.0, "grad unchanged 3");

    double same[] = {1.0, 2.0};
    expect_status(miniai_gradient_forward_safe(f_valid, same, 2, 1e-6, NULL, same), 0, "aliasing ok");
    expect_near(same[0], 2.0, "aliasing value 1");
    expect_near(same[1], 4.0, "aliasing value 2");
}

int main(void) {
    printf("tests running\n");
    test_gradient_errors();
    printf("tests finished\n");
    return failures != 0;
}
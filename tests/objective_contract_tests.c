#include "miniai/objective.h"
#include "miniai/gradient.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

static int failures = 0;

static void check(int ok, const char *name) {
    if (!ok) {
        printf("FAIL: %s\n", name);
        failures++;
    }
}

static int near(double actual, double expected) {
    return isfinite(actual) && isfinite(expected) &&
           fabs(actual - expected) <= 1e-12 + 1e-9 * fmax(fabs(actual), fabs(expected));
}


static double sum_squares(const double x[], size_t n, void *context) {
    (void)context;
    if (x == NULL || n == 0) {
        return NAN;
    }
    double sum = 0.0;
    for (size_t i = 0; i < n; i++) {
        sum += x[i] * x[i];
    }
    return sum;
}

int main(void) {
    miniai_objective_function f = sum_squares;

    const double x1[] = {3.0};
    check(near(f(x1, 1, NULL), 9.0), "n=1: F(3) = 9");

    double x2[] = {1.0, 2.0};
    double copy[] = {1.0, 2.0};
    check(near(f(x2, 2, NULL), 5.0), "n=2: F(1,2) = 5");
    check(memcmp(x2, copy, sizeof x2) == 0, "input x is unchanged");

    check(isnan(f(NULL, 2, NULL)), "x == NULL -> NAN");
    check(isnan(f(x2, 0, NULL)), "n == 0 -> NAN");

    check(MINIAI_GRADIENT_OK == 0, "OK status is 0");

    if (failures != 0) {
        printf("%d check(s) failed\n", failures);
        return 1;
    }
    printf("All objective contract checks passed\n");
    return 0;
}
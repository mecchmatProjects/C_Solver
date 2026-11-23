
#include "miniai/math/vector.h"
#include <math.h>
#include <stdio.h>

static int failures = 0;


static void check(const char *name, double actual, double expected) {
    int passed;

    if (isnan(expected)) {
        passed = isnan(actual);
    } else if (isinf(expected)) {
        passed = isinf(actual) && actual == expected;
    } else {
        passed = isfinite(actual) &&
                 fabs(actual - expected) <= 1e-12;
    }

    printf("%s: %s\n", passed ? "PASS" : "FAIL", name);

    if (!passed) {
        failures++;
    }
}

int main(void) {
    double a[] = {-3.0, 4.0};
    double b[] = {0.0};
    double c[] = {-1.0, -2.0, -3.0};
    double d[] = {1.5, -2.5, 3.0};
    double e[] = {NAN, 2.0};
    double f[] = {INFINITY, 1.0};

    check("Basic", miniai_vector_l1_norm(a, 2), 7.0);
    check("Zero", miniai_vector_l1_norm(b, 1), 0.0);
    check("Negative", miniai_vector_l1_norm(c, 3), 6.0);
    check("Fractional", miniai_vector_l1_norm(d, 3), 7.0);
    check("Empty", miniai_vector_l1_norm(NULL, 0), 0.0);
    check("NULL pointer", miniai_vector_l1_norm(NULL, 2), NAN);
    check("NaN input", miniai_vector_l1_norm(e, 2), NAN);
    check("Infinity input", miniai_vector_l1_norm(f, 2), INFINITY);

    printf("\nPassed: %d/8\n", 8 - failures);

    return failures == 0 ? 0 : 1;
}

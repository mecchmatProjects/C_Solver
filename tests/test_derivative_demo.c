
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MINIAI_A6_TEST_BUILD
#include "../examples/derivative_demo.c"

static int failures = 0;
static int checks = 0;

static void check_near(const char *name, double actual,
                       double expected, double tolerance) {
    ++checks;

    if (!isfinite(actual) || fabs(actual - expected) > tolerance) {
        fprintf(stderr, "FAIL %s: actual=%.12g, expected=%.12g\n",
                name, actual, expected);
        ++failures;
    }
}

static void check_nan(const char *name, double actual) {
    ++checks;

    if (!isnan(actual)) {
        fprintf(stderr, "FAIL %s: expected NAN, actual=%.12g\n",
                name, actual);
        ++failures;
    }
}

static void check_true(const char *name, int condition) {
    ++checks;

    if (!condition) {
        fprintf(stderr, "FAIL %s\n", name);
        ++failures;
    }
}

static void test_table_format(void) {
    FILE *f = tmpfile();

    check_true("tmpfile created", f != NULL);
    if (f == NULL)
        return;

    check_true("table written",
               print_derivative_table(f) == EXIT_SUCCESS);

    rewind(f);

    char line[256];

    check_true("header exists",
               fgets(line, sizeof(line), f) != NULL);

    check_true("header has columns",
               strstr(line, "Exact") != NULL &&
               strstr(line, "Approximation") != NULL &&
               strstr(line, "Absolute error") != NULL);

    int rows = 0;
    int has_smallest_h = 0;
    int has_largest_h = 0;

    while (fgets(line, sizeof(line), f) != NULL) {
        ++rows;

        if (strstr(line, "1.0e-08") != NULL)
            has_smallest_h = 1;

        if (strstr(line, "1.0e-01") != NULL)
            has_largest_h = 1;
    }

    check_true("72 result rows", rows == 72);
    check_true("h=1e-1 shown", has_largest_h);
    check_true("h=1e-8 shown", has_smallest_h);

    fclose(f);
}

int main(void) {
    check_near("forward x^2",
               derivative_forward(square, 2.0, 0.1),
               4.1, 1e-12);

    check_near("backward x^2",
               derivative_backward(square, 2.0, 0.1),
               3.9, 1e-12);

    check_near("central x^2",
               derivative_central(square, 2.0, 0.1),
               4.0, 1e-12);

    check_near("central sin",
               derivative_central(sin, 0.0, 1e-4),
               1.0, 1e-8);

    check_near("central exp",
               derivative_central(exp, 0.0, 1e-4),
               1.0, 1e-8);

    check_near("large h",
               derivative_forward(square, 2.0, 1.0),
               5.0, 1e-12);

    double forward_error =
        fabs(derivative_forward(exp, 0.0, 0.1) - 1.0);

    double central_error =
        fabs(derivative_central(exp, 0.0, 0.1) - 1.0);

    check_true("central better than forward for exp at h=0.1",
               central_error < forward_error);

    check_nan("zero h",
              derivative_forward(square, 2.0, 0.0));

    check_nan("negative h",
              derivative_backward(square, 2.0, -0.1));

    check_nan("NAN h",
              derivative_central(square, 2.0, NAN));

    check_nan("INF h",
              derivative_forward(square, 2.0, INFINITY));

    check_nan("NULL callback",
              derivative_central(NULL, 2.0, 0.1));

    check_nan("nonfinite function result",
              derivative_forward(exp, 1000.0, 0.1));

    check_nan("x+h overflow",
              derivative_forward(square, DBL_MAX, DBL_MAX));

    check_true("NULL output stream rejected",
               print_derivative_table(NULL) == EXIT_FAILURE);

    test_table_format();

    if (failures == 0) {
        printf("A6: all %d checks passed\n", checks);
        return EXIT_SUCCESS;
    }

    fprintf(stderr, "A6: %d of %d checks failed\n",
            failures, checks);

    return EXIT_FAILURE;
}

#include <math.h>
#include <stdio.h>
#include <float.h>

#include <miniai/ml/loss/losses.h>

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

static void expect_status(double actual, double expected,
                          const char *message) {
    ++checks;
    if (actual != expected) {
        fprintf(stderr, "FAIL: %s (status %d, expected %d)\n", message,
                (int)actual, (int)expected);
        ++failures;
    }
}

static void test_absolute_error_basic(void) {
    expect_near(miniai_absolute_error(3.0, 2.0), 1.0,
        "absolute error1");
    expect_near(miniai_absolute_error(1.0, 3.0), 2.0,
        "absolute error2");
    expect_near(miniai_absolute_error(3.0, 3.0), 0.0,
        "absolute error3");
    expect_status(miniai_absolute_error(-0.0, 0.0), 0.0,
        "absolute error4");
    expect_near(miniai_absolute_error(NAN, 1.0), NAN,
        "absolute error5");
}
int main() {
    printf("tests running\n");
    test_absolute_error_basic();
    printf("tests finished\n");
    return failures != 0;
}
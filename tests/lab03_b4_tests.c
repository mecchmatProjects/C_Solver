#include <math.h>
#include <stdio.h>

#include "miniai/math/statistics.h"

static int failures = 0;
static int checks = 0;

static void expect_near(double actual, double expected, const char *message) {
    ++checks;
    if (isnan(expected) ? !isnan(actual) : !(fabs(actual - expected) <= 1e-12)) {
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

static void test_population_variance( void ) {
    double data1[] = {1, 2, 3};
    double data2[] = {1, 1, 1};
    double data3[] = {7};
    expect_near(miniai_variance( data1, 3 ), 2.0/3,
        "variance error of {1, 2, 3}" );
    expect_status(miniai_variance( data2, 3 ), 0.0,
        "variance error of constant" );
    expect_status(miniai_variance( data3, 1 ), 0.0,
        "variance error of singleton" );
    expect_near(miniai_variance( data1, 0 ), NAN,
        "variance error for n=0" );
    expect_near(miniai_variance( NULL, 1 ), NAN,
        "variance error for NULL" );
}
int main() {
    printf("tests running\n");
    test_population_variance();
    printf("tests finished\n");
}
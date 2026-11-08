#include <math.h>
#include <stdio.h>

#include "miniai/math/statistics.h"

static int failures = 0;
static int checks = 0;

static void expect_near(double actual, double expected, const char *message) {
    ++checks;
    if (!(fabs(actual - expected) <= 1e-16)) {
        fprintf(stderr, "FAIL: %s (actual &.17g, expected %.17g)\n", message, actual, expected);
        ++failures;
    }
}

static void expected_zero(int actual, const char *message){
    ++checks;
    if (actual != 0){
        fprintf(stderr, "FAIL: %s (code %d, expected 0)\n", message, actual);
        ++failures;
    }
}

static void expected_nonzero(int actual, const char *message) {
    ++checks;
    if (actual == 0) {
        fprintf(stderr, "FAIL: %s (code 0, expected non-zero)\n", message);
        ++failures;
    }
}

static void test_mandatory(void) {
    // Instructor's mandatory test: [-1, 0, 1] -> mean=0, std=1; in-place
    double arr[] = {-1.0, 0.0, 1.0};
    
    expect_zero(miniai_standardize(arr, arr, 3), "mandatory [-1, 0, 1] in-place standardization");
    expect_near(arr[0], -1.0, "mandatory first component");
    expect_near(arr[1], 0.0,  "mandatory second component");
    expect_near(arr[2], 1.0,  "mandatory third component");
}

static void test_normal_case(void) {
    // General case with out-of-place execution
    const double in[] = {2.0, 4.0, 4.0, 4.0, 5.0, 5.0, 7.0, 9.0};
    double out[8] = {0.0};
    
    expect_zero(miniai_standardize(in, out, 8), "standardize general array");
    // Standardized value at index 0 should be approx -1.3363062
    expect_near(out[0], -1.3363062, "general standard deviation first component");
}

static void test_empty(void) {
    double out[1] = {42.0};
    
    // n=0 should return an error as per requirements
    expect_nonzero(miniai_standardize(NULL, NULL, 0), "reject empty standardization (n=0)");
    expect_nonzero(miniai_standardize(out, out, 0), "reject empty standardization with pointers");
}

static void test_zero_stddev(void) {
    const double in[] = {5.0, 5.0, 5.0};
    double out[3] = {0.0};

    // std=0 should return an error
    expect_nonzero(miniai_standardize(in, out, 3), "reject standard deviation of 0");
}

static void test_null_arguments(void) {
    const double in[] = {1.0, 2.0, 3.0};
    double out[3] = {42.0, 42.0, 42.0};

    expect_nonzero(miniai_standardize(NULL, out, 3), "reject NULL in");
    expect_nonzero(miniai_standardize(in, NULL, 3), "reject NULL out");
    expect_near(out[0], 42.0, "failed call leaves output unchanged");
}

int main(void) {
    test_mandatory();
    test_normal_case();
    test_empty();
    test_zero_stddev();
    test_null_arguments();

    if (failures != 0) {
        fprintf(stderr, "%d of %d standardization checks failed\n", failures,
                checks);
        return 1;
    }

    printf("%d standardization checks passed\n", checks);
    return 0;
}
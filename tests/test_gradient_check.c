#include "miniai/gradient_check.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// Helper to open a temporary file for capturing report output safely on all OSes
static FILE *open_temp_report(const char *filename) {
    FILE *fp = fopen(filename, "w+");
    assert(fp != NULL);
    return fp;
}

// Test 1: Matching gradients within tolerance should return 0 and print PASS
static void test_pass_case(void) {
    const double exact[] = {2.0, 12.0, 0.0};
    const double approx[] = {2.0 + 1e-7, 12.0 - 1e-6, 1e-9};
    const char *tmp_name = "test_grad_pass.tmp";

    FILE *fp = open_temp_report(tmp_name);
    int status = miniai_gradient_check_report(fp, exact, approx, 3, 1e-6, 1e-5);
    assert(status == 0);

    rewind(fp);
    char buf[1024] = {0};
    size_t read_bytes = fread(buf, 1, sizeof(buf) - 1, fp);
    assert(read_bytes > 0);
    assert(strstr(buf, "PASS") != NULL);
    assert(strstr(buf, "FAIL") == NULL);

    fclose(fp);
    remove(tmp_name);
}



// Test 2: Intentional error in analytical gradient should return 1 and flag the coordinate
static void test_intentional_mismatch(void) {
    const double exact[] = {2.0, 99.0, -4.0}; // coordinate 1 is intentionally wrong
    const double approx[] = {2.0, 12.0, -4.0};
    const char *tmp_name = "test_grad_fail.tmp";

    FILE *fp = open_temp_report(tmp_name);
    int status = miniai_gradient_check_report(fp, exact, approx, 3, 1e-6, 1e-5);
    assert(status == 1);

    rewind(fp);
    char buf[1024] = {0};
    size_t read_bytes = fread(buf, 1, sizeof(buf) - 1, fp);
    assert(read_bytes > 0);
    assert(strstr(buf, "1,99,12,") != NULL);
    assert(strstr(buf, "FAIL") != NULL);

    fclose(fp);
    remove(tmp_name);
}



// Test 3: Invalid argument (NULL stream/pointers, n == 0, negative tolerances) return -1
static void test_invalid_arguments(void) {
    const double exact[] = {1.0, 2.0};
    const double approx[] = {1.0, 2.0};

    assert(miniai_gradient_check_report(NULL, exact, approx, 2, 1e-6, 1e-6) == -1);
    assert(miniai_gradient_check_report(stdout, NULL, approx, 2, 1e-6, 1e-6) == -1);
    assert(miniai_gradient_check_report(stdout, exact, NULL, 2, 1e-6, 1e-6) == -1);
    assert(miniai_gradient_check_report(stdout, exact, approx, 2, 1e-6, -1e-6) == -1);
    assert(miniai_gradient_check_report(stdout, exact, approx, 0, 1e-6, 1e-6) == -1);
    assert(miniai_gradient_check_report(stdout, exact, approx, 2, -1e-6, 1e-6) == -1);
    assert(miniai_gradient_check_report(stdout, exact, approx, 2, 1e-6, -1e-6) == -1);
    assert(miniai_gradient_check_report(stdout, exact, approx, 2, NAN, 1e-6) == -1);

}



// Test 4: NaN or Inf inside gradient arrays should return -1
static void test_nonfinite_components(void) {
    const double exact_nan[] = {1.0, NAN};
    const double approx_ok[] = {1.0, 2.0};
    const double approx_inf[] = {1.0, INFINITY};

    assert(miniai_gradient_check_report(stdout, exact_nan, approx_ok, 2, 1e-6, 1e-6) == -1);
    assert(miniai_gradient_check_report(stdout, approx_ok, approx_inf, 2, 1e-6, 1e-6) == -1);

}




int main(void) {
    test_pass_case();
    test_intentional_mismatch();
    test_invalid_arguments();
    test_nonfinite_components();

    printf("All gradient_checks test passed!\n");
    return 0;
}
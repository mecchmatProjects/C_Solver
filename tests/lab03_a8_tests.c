#include "miniai/math/vector.h"

#include <math.h>
#include <stdio.h>

#define ABS_TOL 1e-12
#define REL_TOL 1e-9

static int almost_equal(double a, double b, double abs_tol, double rel_tol) {
    if (!isfinite(a) || !isfinite(b)) {
        return 0;
    }
    return fabs(a - b) <= abs_tol + rel_tol * fmax(fabs(a), fabs(b));
}

int main(void) {
    int failures = 0;

    {
        const double a[] = {0.0, 0.0};
        const double b[] = {3.0, 4.0};
        double res = miniai_vector_distance(a, b, 2);
        if (!almost_equal(res, 5.0, ABS_TOL, REL_TOL)) {
            fprintf(stderr, "FAIL Test 1: expected 5.0, got %.15f\n", res);
            ++failures;
        }
    }


    {
        const double a[] = {-2.5, 0.0, 7.25, 100.0};
        const double b[] = {-2.5, 0.0, 7.25, 100.0};
        double res = miniai_vector_distance(a, b, 4);
        if (!almost_equal(res, 0.0, ABS_TOL, REL_TOL)) {
            fprintf(stderr, "FAIL Test 2: expected 0.0, got %.15f\n", res);
            ++failures;
        }
    }


    {
        const double a[] = {-1.0, -2.0, 3.0};
        const double b[] = {2.0, 2.0, -9.0};
        double dab = miniai_vector_distance(a, b, 3);
        double dba = miniai_vector_distance(b, a, 3);
        if (!almost_equal(dab, 13.0, ABS_TOL, REL_TOL) ||
            !almost_equal(dba, 13.0, ABS_TOL, REL_TOL)) {
            fprintf(stderr, "FAIL Test 3: expected 13.0, got dab=%.15f, dba=%.15f\n", dab, dba);
            ++failures;
        }
    }

    {
        const double a[] = {1.0, 2.0};
        const double b[] = {3.0, 4.0};
        double res1 = miniai_vector_distance(a, b, 0);
        double res2 = miniai_vector_distance(NULL, NULL, 0);
        if (!almost_equal(res1, 0.0, ABS_TOL, REL_TOL) ||
            !almost_equal(res2, 0.0, ABS_TOL, REL_TOL)) {
            fprintf(stderr, "FAIL Test 4: expected 0.0 for n=0\n");
            ++failures;
        }
    }


    {
        const double v[] = {1.0, 2.0};
        if (!isnan(miniai_vector_distance(NULL, v, 2)) ||
            !isnan(miniai_vector_distance(v, NULL, 2)) ||
            !isnan(miniai_vector_distance(NULL, NULL, 2))) {
            fprintf(stderr, "FAIL Test 5: expected NAN for NULL pointers with n > 0\n");
            ++failures;
        }
    }


    {
        const double valid[] = {1.0, 2.0};
        const double with_nan[] = {1.0, NAN};
        const double with_inf[] = {INFINITY, 2.0};
        if (!isnan(miniai_vector_distance(with_nan, valid, 2)) ||
            !isnan(miniai_vector_distance(valid, with_inf, 2))) {
            fprintf(stderr, "FAIL Test 6: expected NAN for NaN/Inf inputs\n");
            ++failures;
        }
    }


    {
        const double a[] = {0.0, 0.0};
        const double b[] = {3e200, 4e200};
        double res = miniai_vector_distance(a, b, 2);
        if (!almost_equal(res, 5e200, ABS_TOL, REL_TOL)) {
            fprintf(stderr, "FAIL Test 7: expected 5e200, got %e\n", res);
            ++failures;
        }
    }

    if (failures != 0) {
        fprintf(stderr, "lab03_a8_tests: FAILED with %d error(s)\n", failures);
        return 1;
    }

    printf("All lab03_a8_tests passed successfully.\n");
    return 0;
}
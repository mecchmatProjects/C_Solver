#include "miniai/gradient_check.h"

#include <math.h>

static const double MINIAI_DENIMINATOR_FLOOR = 1e-12;

// computes absolute error for single coordinate
static double compute_abs_error(double exact_val, double approx_val) {
    return fabs(exact_val - approx_val);
}

// computes relative error using denominator floor to avoid division by zero
static double compute_rel_error(double exact_val, double abs_err) {
    double denom = fmax(fabs(exact_val), MINIAI_DENIMINATOR_FLOOR);
    return abs_err / denom;
}



int miniai_gradient_check_report(FILE *stream, const double exact[], 
                                const double approx[], size_t n, 
                                double abs_tol, double rel_tol) {
    // Validate pointers, size and tolerances
    if (stream == NULL || exact == NULL || approx == NULL || n == 0) {
        return -1;
    }
    if (!isfinite(abs_tol) || abs_tol < 0.0 || !isfinite(rel_tol) || rel_tol < 0.0) {
        return -1;
    }

    // Validate that all gradient components are finite (no NaN or Inf)
    for (size_t i = 0; i < n; ++i) {
        if (!isfinite(exact[i]) || !isfinite(approx[i])) {
            return -1;
        }
    }

    // Print machine-readable CSV header
    if (fprintf(stream, "index,exact,numeratical,abs_error,rel_error,status\n") < 0) {
        return -1;
    }

    // Compare each coordinate and print results
    int has_mismatch = 0;

    for (size_t i = 0; i < n; ++i) {
        double abs_err = compute_abs_error(exact[i], approx[i]);
        double rel_err = compute_rel_error(exact[i], abs_err);
        double limit = abs_tol + rel_tol * fabs(exact[i]);

        int passed = (abs_err <= limit);
        if (!passed) {
            has_mismatch = 1;
        }

        if (fprintf(stream, "%zu,%.12g,%.12g,%.12g,%.12g,%s\n",
                    i, exact[i], approx[i], abs_err, rel_err,
                passed ? "PASS" : "FAIL") < 0) {
                    return -1;
        }
    }

    return has_mismatch ? 1 : 0;

}
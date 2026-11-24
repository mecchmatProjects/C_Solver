#include "miniai/differentiation_experiments.h"

#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int miniai_step_sweep(miniai_scalar_function f, double exact, double x,
    const double steps[], size_t n,
    double errors[], size_t* best_index) {
    if (f == NULL || !isfinite(exact) || !isfinite(x) ||
        steps == NULL || n == 0 || errors == NULL || best_index == NULL) {
        return 1;
    }
    if (n > SIZE_MAX / sizeof(double)) {
        return 2;
    }

    double* tmp = (double*)malloc(n * sizeof(double));
    if (tmp == NULL) {
        return 3;
    }

    size_t best_idx = 0;
    double best_err = INFINITY;

    for (size_t i = 0; i < n; ++i) {
        double approx = miniai_derivative_central(f, x, steps[i]);
        if (!isfinite(approx)) {
            free(tmp);
            return 4;
        }
        double err = fabs(approx - exact);
        if (!isfinite(err)) {
            free(tmp);
            return 4;
        }
        tmp[i] = err;
        if (i == 0 || err < best_err) {
            best_err = err;
            best_idx = i;
        }
    }

    memcpy(errors, tmp, n * sizeof(double));
    *best_index = best_idx;
    free(tmp);
    return 0;
}
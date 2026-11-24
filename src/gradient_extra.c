#include "miniai/gradient_extra.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

int miniai_gradient_central_steps(miniai_objective_function f,
                                  const double x[],
                                  const double steps[],
                                  size_t n,
                                  void *context,
                                  double gradient[]) {

    if (f == NULL || x == NULL || steps == NULL || gradient == NULL || n == 0) {
        return MINIAI_GRADIENT_INVALID_ARGUMENT;
    }
    if (x == gradient) {
        return MINIAI_GRADIENT_INVALID_ARGUMENT;
    }


    double *tmp_x = malloc(n * sizeof(double));
    double *tmp_grad = malloc(n * sizeof(double));
    if (tmp_x == NULL || tmp_grad == NULL) {
        free(tmp_x);
        free(tmp_grad);
        return MINIAI_GRADIENT_NO_MEMORY;
    }

    memcpy(tmp_x, x, n * sizeof(double));

    for (size_t i = 0; i < n; i++) {
        double h = steps[i];

        if (!isfinite(h) || h <= 0.0) {
            free(tmp_x);
            free(tmp_grad);
            return MINIAI_GRADIENT_INVALID_ARGUMENT;
        }

        double x_plus = x[i] + h;
        double x_minus = x[i] - h;
        if (!isfinite(x_plus) || !isfinite(x_minus)) {
            free(tmp_x);
            free(tmp_grad);
            return MINIAI_GRADIENT_NONFINITE_OBJECTIVE;
        }
        tmp_x[i] = x_plus;
        double f_plus = f(tmp_x, n, context);

        tmp_x[i] = x_minus;
        double f_minus = f(tmp_x, n, context);

        tmp_x[i] = x[i];

        if (!isfinite(f_plus) || !isfinite(f_minus)) {
            free(tmp_x);
            free(tmp_grad);
            return MINIAI_GRADIENT_NONFINITE_OBJECTIVE;
        }

        tmp_grad[i] = (f_plus - f_minus) / (2.0 * h);
        if (!isfinite(tmp_grad[i])) {
            free(tmp_x);
            free(tmp_grad);
            return MINIAI_GRADIENT_NONFINITE_OBJECTIVE;
        }
    }
    memcpy(gradient, tmp_grad, n * sizeof(double));

    free(tmp_x);
    free(tmp_grad);
    return MINIAI_GRADIENT_OK;
}
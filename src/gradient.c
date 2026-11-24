#include "miniai/gradient.h"

#include <math.h>
#include <stdlib.h>


static int miniai_valid_step(double h)
{
    return isfinite(h) && h > 0.0;
}






static double miniai_objective_shifted(miniai_objective_function f,
                                       const double xp[],
                                       size_t i,
                                       double delta,
                                       size_t n,
                                       void *context)
{
    double value;

    ((double *)xp)[i] += delta;
    value = f(xp, n, context);
    ((double *)xp)[i] -= delta;

    return value;
}

int miniai_gradient_central(miniai_objective_function f,
                            const double x[],
                            size_t n,
                            double h,
                            void *context,
                            double gradient[])
{
    double *tmp;
    double *result;
    size_t i;

    if (f == NULL || x == NULL || gradient == NULL || n == 0) {
        return MINIAI_GRADIENT_INVALID_ARGUMENT;
    }
    if (!miniai_valid_step(h)) {
        return MINIAI_GRADIENT_INVALID_ARGUMENT;
    }
    for (i = 0; i < n; ++i) {
        if (!isfinite(x[i])) {
            return MINIAI_GRADIENT_INVALID_ARGUMENT;
        }
        if (!isfinite(x[i] + h) || !isfinite(x[i] - h)) {
            return MINIAI_GRADIENT_INVALID_ARGUMENT;
        }
    }


    tmp = (double *)malloc(n * sizeof(*tmp));
    if (tmp == NULL) {
        return MINIAI_GRADIENT_NO_MEMORY;
    }
    result = (double *)malloc(n * sizeof(*result));
    if (result == NULL) {
        free(tmp);
        return MINIAI_GRADIENT_NO_MEMORY;
    }

    for (i = 0; i < n; ++i) {
        double f_plus;
        double f_minus;


        for (size_t j = 0; j < n; ++j) {
            tmp[j] = x[j];
        }

        f_plus = miniai_objective_shifted(f, tmp, i, +h, n, context);
        f_minus = miniai_objective_shifted(f, tmp, i, -h, n, context);
        if (!isfinite(f_plus) || !isfinite(f_minus)) {
            free(result);
            free(tmp);
            return MINIAI_GRADIENT_NONFINITE_OBJECTIVE;
        }
        result[i] = (f_plus - f_minus) / (2.0 * h);
        if (!isfinite(result[i])) {
            free(result);
            free(tmp);
            return MINIAI_GRADIENT_NONFINITE_OBJECTIVE;
        }
    }

    for (i = 0; i < n; ++i) {
        gradient[i] = result[i];
    }

    free(result);
    free(tmp);
    return MINIAI_GRADIENT_OK;
}

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include "miniai/gradient_extra.h"

static double my_func(const double x[], size_t n, void *context) {
    (void)context;
    if (n < 2) {
        return NAN;
    }
    return x[0] * x[0] + 3.0 * x[1] * x[1];
}

static double bad_func(const double x[], size_t n, void *context) {
    (void)x;
    (void)n;
    (void)context;
    return NAN;
}

int main(void) {

    {
        const double x[2] = {1.0, 2.0};
        const double steps[2] = {0.0001, 0.0001};
        double grad[2] = {0.0, 0.0};

        int rc = miniai_gradient_central_steps(my_func, x, steps, 2, NULL, grad);
        assert(rc == MINIAI_GRADIENT_OK);
        assert(fabs(grad[0] - 2.0) < 1e-5);
        assert(fabs(grad[1] - 12.0) < 1e-5);
    }

    {
        const double x[2] = {1.0, 1000.0};
        const double steps[2] = {0.001, 0.1};
        double grad[2] = {0.0, 0.0};

        int rc = miniai_gradient_central_steps(my_func, x, steps, 2, NULL, grad);
        assert(rc == MINIAI_GRADIENT_OK);
        assert(fabs(grad[0] - 2.0) < 1e-5);
        assert(fabs(grad[1] - 6000.0) < 1e-2);
    }

    {
        const double x[2] = {1.0, 2.0};
        const double bad_steps[2] = {0.01, 0.0};
        double grad[2] = {77.0, 88.0};

        assert(miniai_gradient_central_steps(NULL, x, bad_steps, 2, NULL, grad) !=
               MINIAI_GRADIENT_OK);
        assert(miniai_gradient_central_steps(my_func, x, NULL, 2, NULL, grad) !=
               MINIAI_GRADIENT_OK);
        assert(miniai_gradient_central_steps(my_func, x, bad_steps, 2, NULL, grad) !=
               MINIAI_GRADIENT_OK);
        assert(grad[0] == 77.0 && grad[1] == 88.0);
    }

    {
        const double x[2] = {1.0, 2.0};
        const double steps[2] = {0.01, 0.01};
        double grad[2] = {55.0, 66.0};

        assert(miniai_gradient_central_steps(bad_func, x, steps, 2, NULL, grad) !=
               MINIAI_GRADIENT_OK);
        assert(grad[0] == 55.0 && grad[1] == 66.0);
    }
    printf("Tests OK\n");
    return 0;
}
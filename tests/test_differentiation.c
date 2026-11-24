#include "miniai/differentiation.h"

#ifdef NDEBUG
#undef NDEBUG
#endif

#include <assert.h>
#include <float.h>
#include <math.h>
#include <stdio.h>

static int near(double actual, double expected) {
    return isfinite(actual) && isfinite(expected) &&
        fabs(actual - expected) <= 1e-12 +
        1e-9 * fmax(fabs(actual), fabs(expected));
}

static double square(double x) {
    return x * x;
}

static double nonfinite(double x) {
    return x > 0.0 ? NAN : INFINITY;
}

int main(void) {
    double h = 0.125;
    double coarse = miniai_derivative_forward(square, 2.0, h);
    double fine = miniai_derivative_forward(square, 2.0, h / 2.0);

    assert(near(coarse, 4.0 + h));
    assert(near(fine, 4.0 + h / 2.0));
    assert(near(fabs(coarse - 4.0), 2.0 * fabs(fine - 4.0)));

    assert(near(miniai_derivative_forward(square, 2.0, 1e-5), 4.0 + 1e-5));
    assert(fabs(miniai_derivative_forward(square, 2.0, 1e-5) - 4.0) < 2e-5);
    assert(near(miniai_derivative_forward(sin, 0.0, 1e-5), 1.0));

    assert(isnan(miniai_derivative_forward(NULL, 2.0, h)));
    assert(isnan(miniai_derivative_forward(square, 2.0, 0.0)));
    assert(isnan(miniai_derivative_forward(square, 2.0, -h)));
    assert(isnan(miniai_derivative_forward(square, 2.0, NAN)));
    assert(isnan(miniai_derivative_forward(square, 2.0, INFINITY)));

    assert(isnan(miniai_derivative_forward(square, NAN, h)));
    assert(isnan(miniai_derivative_forward(square, INFINITY, h)));
    assert(isnan(miniai_derivative_forward(square, DBL_MAX, DBL_MAX)));

    assert(isnan(miniai_derivative_forward(nonfinite, 1.0, h)));
    assert(isnan(miniai_derivative_forward(nonfinite, -1.0, h)));
    assert(isnan(miniai_derivative_forward(sqrt, -1.0, 2.0)));
    assert(isnan(miniai_derivative_forward(square, 0.0, DBL_MAX)));

    const double steps[] = {1e-1, 1e-2, 1e-3, 1e-8, 1e-16};

    for (size_t i = 0; i < sizeof(steps) / sizeof(steps[0]); ++i) {
        double d = miniai_derivative_forward(square, 2.0, steps[i]);

        printf("h=%.0e approximation=%.12g error=%.12g\n",
               steps[i], d, fabs(d - 4.0));
    }

    printf("fabs at 0: %.12g\n",
           miniai_derivative_forward(fabs, 0.0, 1e-3));

    return 0;
}

#include "test_functions.h"

#undef NDEBUG
#include <assert.h>
#include <math.h>

static double central_difference(double (*f)(double), double x) {
    const double h = 0.00001;
    return (f(x + h) - f(x - h)) / (2.0 * h);
}

static void check_close(double actual, double expected, double tolerance) {
    const double limit = tolerance + tolerance * fabs(expected);
    assert(fabs(actual - expected) <= limit);
}

int main(void) {
    for (int point = -1; point <= 1; ++point) {
        const double x = point;
        check_close(test_poly_x2(x), x * x, 1e-14);
        check_close(test_sin(x), sin(x), 1e-14);
        check_close(test_exp(x), exp(x), 1e-14);
        check_close(central_difference(test_poly_x2, x), 2.0 * x, 1e-9);
        check_close(central_difference(test_sin, x), cos(x), 1e-9);
        check_close(central_difference(test_exp, x), exp(x), 1e-9);
    }

    const double periodic_x = 0.3;
    const double period = 2.0 * acos(-1.0);
    check_close(test_sin(periodic_x + period), test_sin(periodic_x), 1e-14);

    const double overflow = test_exp(1000.0);
    assert(isinf(overflow) && overflow > 0.0);
    return 0;
}

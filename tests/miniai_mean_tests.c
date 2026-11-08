#include "miniai/math/statistics.h"
#include <assert.h>
#include <math.h>
#include <stddef.h>

int main(void) {
    double a[] = {1.0, 2.0, 3.0, 4.0};
    double b[] = {7.0};
    double c[] = {-2.0, 0.0, 2.0};
    double d[] = {-5.0, -3.0, -1.0};

    assert(fabs(miniai_mean(a, 4) - 2.5) < 1e-9);
    assert(fabs(miniai_mean(b, 1) - 7.0) < 1e-9);
    assert(isnan(miniai_mean(a, 0)));
    assert(isnan(miniai_mean(NULL, 1)));
    assert(fabs(miniai_mean(c, 3) - 0.0) < 1e-9);

    return 0;
}
#include "miniai/math/vector.h"
#include <assert.h>
#include <math.h>
#include <stddef.h>

int main(void) {
    double a[] = {1.0, 2.0, 3.0};
    double b[] = {-2.0, 2.0, 0.0};
    double c[] = {5.5};
    double d[] = {0.0, 0.0};

    assert(fabs(miniai_vector_sum(a, 3) - 6.0) < 1e-9);
    assert(fabs(miniai_vector_sum(b, 3)) < 1e-9);
    assert(fabs(miniai_vector_sum(c, 1) - 5.5) < 1e-9);
    assert(fabs(miniai_vector_sum(d, 2)) < 1e-9);
    assert(miniai_vector_sum(NULL, 0) == 0.0);
    assert(miniai_vector_sum(a, 0) == 0.0);

    return 0;
}

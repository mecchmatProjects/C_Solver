#include "miniai/math/vector.h"

int miniai_vector_subtract(const double a[], const double b[], double out[],
                           size_t n) {
    size_t index;

    if (n == 0) {
        return 0;
    }
    if (a == NULL || b == NULL || out == NULL) {
        return 1;
    }

    for (index = 0; index < n; ++index) {
        out[index] = a[index] - b[index];
    }
    return 0;
}
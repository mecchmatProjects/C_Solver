
#include "miniai/math/vector.h"

#include <assert.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>

int main(void)
{
    // Test 1: Positive and negative values
    const double v1[] = {-3.0, 4.0};
    assert(miniai_vector_l1_norm(v1, 2) == 7.0);

    // Test 2: Zero vector
    const double v2[] = {0.0};
    assert(miniai_vector_l1_norm(v2, 1) == 0.0);

    // Test 3: Empty vector
    assert(miniai_vector_l1_norm(NULL, 0) == 0.0);

    // Test 4: Multiple elements
    const double v3[] = {1.0, -2.0, 3.0, -4.0};
    assert(miniai_vector_l1_norm(v3, 4) == 10.0);

    // Test 5: NULL with nonzero length
    assert(isnan(miniai_vector_l1_norm(NULL, 3)));

    // Test 6: NaN element
    const double v4[] = {1.0, NAN, 2.0};
    assert(isnan(miniai_vector_l1_norm(v4, 3)));

    // Test 7: All negative values
    const double v5[] = {-1.0, -5.0, -9.0};
    assert(miniai_vector_l1_norm(v5, 3) == 15.0);

    // Test 8: Infinity
    const double v6[] = {1.0, INFINITY};
    assert(isinf(miniai_vector_l1_norm(v6, 2)));

    printf("All 8 L1 norm tests passed.\n");
    return 0;
}

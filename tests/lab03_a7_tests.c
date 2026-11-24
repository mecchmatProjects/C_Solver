#include <math.h>
#include <assert.h>
#include "miniai/math/vector.h"

void test_l2_norm(void) {
    double v1[] = {3.0, 4.0};
    assert(fabs(miniai_l2_norm(v1, 2) - 5.0) < 1e-12);
    
    double v2[] = {1.0, 2.0, 2.0};
    assert(fabs(miniai_l2_norm(v2, 3) - 3.0) < 1e-12);
    
    double v3[] = {0.0, 0.0};
    assert(fabs(miniai_l2_norm(v3, 2) - 0.0) < 1e-12);

    // empty array check (size == 0 -> 0)
    assert(miniai_l2_norm(NULL, 0) == 0.0);
    
    // check NaN
    double bad_v[] = {1.0, NAN};
    assert(isnan(miniai_l2_norm(bad_v, 2)));
}

int main(void) {
    test_l2_norm();
    return 0;
}

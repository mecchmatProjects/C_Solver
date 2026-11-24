#include "miniai/differentiation_experiments.h"
#include "test_functions.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>

static double bad_nan_fn(double x) {
    (void)x;
    return NAN;
}

int main(void) {
    const double steps[] = { 1e-1, 1e-2, 1e-4, 1e-6 };
    double errors[4] = { -1.0, -1.0, -1.0, -1.0 };
    size_t best_index = 999;

    int status = miniai_step_sweep(test_exp, 1.0, 0.0, steps, 4, errors, &best_index);
    assert(status == 0);
    assert(best_index < 4);
    for (size_t i = 0; i < 4; ++i) {
        assert(errors[i] >= 0.0);
        assert(errors[best_index] <= errors[i]);
    }

    /* On error, outputs must remain unchanged */
    double sentinel[2] = { 42.0, 42.0 };
    size_t sentinel_idx = 77;
    assert(miniai_step_sweep(NULL, 1.0, 0.0, steps, 2, sentinel, &sentinel_idx) != 0);
    assert(miniai_step_sweep(test_exp, 1.0, 0.0, steps, 0, sentinel, &sentinel_idx) != 0);
    assert(miniai_step_sweep(bad_nan_fn, 1.0, 0.0, steps, 2, sentinel, &sentinel_idx) != 0);

    const double bad_steps[] = { 1e-2, -1e-3 };
    assert(miniai_step_sweep(test_exp, 1.0, 0.0, bad_steps, 2, sentinel, &sentinel_idx) != 0);
    assert(sentinel[0] == 42.0 && sentinel[1] == 42.0 && sentinel_idx == 77);

    printf("All A7 step sweep tests passed!\n");
    return 0;
}
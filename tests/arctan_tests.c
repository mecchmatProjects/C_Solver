#include <math.h>
#include <assert.h>
#include "miniai/ml/activation/arctan.h"

void test_arctan_basic(void) {
    Activation act;
    assert(activation_arctan_init(&act) == ACTIVATION_STATUS_OK);
    
    double pi = acos(-1.0);
    
    // check values
    assert(fabs(activation_value(&act, 0.0) - 0.0) < 1e-12);
    assert(fabs(activation_value(&act, 1.0) - atan(1.0)) < 1e-12);
    assert(fabs(activation_value(&act, -2.0) - atan(-2.0)) < 1e-12);
    assert(fabs(activation_value(&act, 2.0) - atan(2.0)) < 1e-12);
    
    // check infinity
    assert(fabs(activation_value(&act, INFINITY) - pi/2) < 1e-12);
    assert(fabs(activation_value(&act, -INFINITY) + pi/2) < 1e-12);
    
    // check derivatives
    assert(fabs(activation_derivative(&act, 0.0) - 1.0) < 1e-12);
    assert(fabs(activation_derivative(&act, INFINITY) - 0.0) < 1e-12);
    assert(fabs(activation_derivative(&act, -INFINITY) - 0.0) < 1e-12);
    
    assert(isnan(activation_value(&act, NAN)));
    
    // check NULL
    assert(activation_arctan_init(NULL) == ACTIVATION_STATUS_INVALID_ARGUMENT);
}

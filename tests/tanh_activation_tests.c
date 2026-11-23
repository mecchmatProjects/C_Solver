
#include "miniai/ml/activation/tanh_activation.h"

#include <assert.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>

static int checks = 0;

static void check_close(double actual, double expected) {
    assert(fabs(actual - expected) < 1e-9);
    checks++;
}

int main(void) {
    Activation activation;
    double result = 0.0;

    assert(activation_tanh_init(&activation)
           == ACTIVATION_STATUS_OK);

    double values[] = {-1000.0, -1.0, 0.0, 1.0, 1000.0};

    for (int i = 0; i < 5; ++i) {
        double x = values[i];

        assert(activation_value(&activation, x, &result)
               == ACTIVATION_STATUS_OK);
        check_close(result, tanh(x));

        assert(activation_derivative(&activation, x, &result)
               == ACTIVATION_STATUS_OK);
        double t = tanh(x);
        check_close(result, 1.0 - t * t);
    }

    assert(activation_value(&activation, 0.0, &result)
           == ACTIVATION_STATUS_OK);
    check_close(result, 0.0);

    assert(activation_derivative(&activation, 0.0, &result)
           == ACTIVATION_STATUS_OK);
    check_close(result, 1.0);

    double positive, negative;

    assert(activation_value(&activation, 1.0, &positive)
           == ACTIVATION_STATUS_OK);
    assert(activation_value(&activation, -1.0, &negative)
           == ACTIVATION_STATUS_OK);
    check_close(negative, -positive);

    assert(activation_derivative(&activation, 1.0, &positive)
           == ACTIVATION_STATUS_OK);
    assert(activation_derivative(&activation, -1.0, &negative)
           == ACTIVATION_STATUS_OK);
    check_close(negative, positive);

    assert(activation_tanh_init(NULL)
           == ACTIVATION_STATUS_INVALID_ARGUMENT);

    printf("All %d numerical checks passed.\n", checks);
    return 0;
}

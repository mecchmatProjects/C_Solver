/* Lab 2 A9: short example of the Linear activation through the public API. */
#include <stdio.h>

#include "miniai/ml/activation/linear.h"

int main(void) {
    const double xs[] = {-2.0, 0.0, 2.0};
    Activation activation;
    size_t i;

    if (activation_linear_init(&activation) != ACTIVATION_STATUS_OK) {
        fputs("Linear initialization failed\n", stderr);
        return 1;
    }

    for (i = 0; i < sizeof xs / sizeof xs[0]; ++i) {
        double value;
        double derivative;

        if (activation_value(&activation, xs[i], &value) !=
                ACTIVATION_STATUS_OK ||
            activation_derivative(&activation, xs[i], &derivative) !=
                ACTIVATION_STATUS_OK) {
            fprintf(stderr, "Linear evaluation failed at x=%g\n", xs[i]);
            return 1;
        }
        printf("x=%g  linear(x)=%g  linear'(x)=%g\n", xs[i], value,
               derivative);
    }

    return 0;
}

#include <stdio.h>

#include "miniai/ml/activation/sigmoid.h"

int main(void) {
    Activation sigmoid;
    double result;

    if (activation_sigmoid_init(&sigmoid) != ACTIVATION_STATUS_OK ||
        activation_value(&sigmoid, 0.0, &result) != ACTIVATION_STATUS_OK) {
        fputs("Failed to evaluate sigmoid activation\n", stderr);
        return 1;
    }

    printf("MiniAI C17 bootstrap ready; sigmoid(0) = %.1f\n", result);
    return 0;
}

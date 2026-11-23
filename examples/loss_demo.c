#include <math.h>
#include <stdio.h>

#include "miniai/ml/activation/sigmoid.h"
#include "miniai/ml/loss/losses.h"

int main(void) {
    const double input = 0.75;
    const double target = 0.8;
    const double delta = 0.5;
    Activation sigmoid;
    double prediction;
    double squared_error;
    double absolute_error;
    double binary_cross_entropy;
    double huber_loss;
    double log_cosh_loss;

    if (activation_sigmoid_init(&sigmoid) != ACTIVATION_STATUS_OK ||
        activation_value(&sigmoid, input, &prediction) != ACTIVATION_STATUS_OK) {
        fputs("Failed to evaluate sigmoid activation\n", stderr);
        return 1;
    }

    squared_error = miniai_squared_error(prediction, target);
    absolute_error = miniai_absolute_error(prediction, target);
    binary_cross_entropy = miniai_binary_cross_entropy(prediction, target);
    huber_loss = miniai_huber_loss(prediction, target, delta);
    log_cosh_loss = miniai_log_cosh_loss(prediction, target);
    if (!isfinite(squared_error) || !isfinite(absolute_error) ||
        !isfinite(binary_cross_entropy) || !isfinite(huber_loss) ||
        !isfinite(log_cosh_loss)) {
        fputs("Failed to evaluate one or more loss functions\n", stderr);
        return 1;
    }

    printf("Scalar sigmoid -> loss example\n");
    printf("input=%.6f prediction=%.6f target=%.6f\n", input, prediction,
           target);
    printf("%-22s %s\n", "Loss", "Value");
    printf("%-22s %.9f\n", "Squared error", squared_error);
    printf("%-22s %.9f\n", "Absolute error", absolute_error);
    printf("%-22s %.9f\n", "Binary cross entropy", binary_cross_entropy);
    printf("%-22s %.9f\n", "Huber loss", huber_loss);
    printf("%-22s %.9f\n", "Log-cosh loss", log_cosh_loss);
    return 0;
}

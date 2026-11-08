#include "miniai/math/vector.h"

#include "miniai/ml/activation/relu.h"

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

double miniai_vector_sum(const double v[], size_t n) {
    if (v == NULL || n == 0) {
        return 0.0;
    }

    double sum = 0.0;

    for (size_t i = 0; i < n; ++i) {
        sum += v[i];
    }

    return sum;
}

int miniai_vector_relu(const double in[], double out[], size_t n) {
    Activation relu;
    ActivationStatus status;
    size_t index;

    if (n == 0) {
        return 0;
    }
    if (in == NULL || out == NULL) {
        return (int)ACTIVATION_STATUS_INVALID_ARGUMENT;
    }

    status = activation_relu_init(&relu);
    if (status != ACTIVATION_STATUS_OK) {
        return (int)status;
    }

    for (index = 0; index < n; ++index) {
        double value;

        status = activation_value(&relu, in[index], &value);
        if (status != ACTIVATION_STATUS_OK) {
            return (int)status;
        }
        out[index] = value;
    }

    return 0;
}

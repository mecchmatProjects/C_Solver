#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "miniai/ml/activation/sigmoid.h"

typedef struct {
    const double *input;
    size_t input_count;
    double target;
} NeuronContext;

static int near(double actual, double expected) {
    return isfinite(actual) && isfinite(expected) &&
           fabs(actual - expected) <=
               1e-8 + 1e-7 * fmax(fabs(actual), fabs(expected));
}

static double neuron_objective(const double parameters[], size_t n,
                               void *context) {
    const NeuronContext *neuron;
    Activation sigmoid;
    double z;
    double prediction;
    double error;
    size_t index;

    if (parameters == NULL || context == NULL) {
        return NAN;
    }

    neuron = (const NeuronContext *)context;
    if (n != neuron->input_count + 1 || neuron->input == NULL ||
        !isfinite(neuron->target)) {
        return NAN;
    }

    z = parameters[n - 1];
    for (index = 0; index < neuron->input_count; ++index) {
        if (!isfinite(neuron->input[index]) ||
            !isfinite(parameters[index])) {
            return NAN;
        }
        z += parameters[index] * neuron->input[index];
    }
    if (!isfinite(z)) {
        return NAN;
    }

    if (activation_sigmoid_init(&sigmoid) != ACTIVATION_STATUS_OK ||
        activation_value(&sigmoid, z, &prediction) != ACTIVATION_STATUS_OK ||
        !isfinite(prediction)) {
        return NAN;
    }

    error = prediction - neuron->target;
    return isfinite(error) ? error * error : NAN;
}

static int central_neuron_gradient(const double parameters[], size_t n, double h, void *context, double gradient[]) {
    double *copy;
    double *result;
    size_t index;

    if (parameters == NULL || gradient == NULL || n == 0 ||
        !isfinite(h) || h <= 0.0) {
        return 1;
    }
    for (index = 0; index < n; ++index) {
        if (!isfinite(parameters[index])) {
            return 1;
        }
    }
    if (n > (size_t)-1 / sizeof(*copy)) {
        return 3;
    }

    copy = (double *)malloc(n * sizeof(*copy));
    result = (double *)malloc(n * sizeof(*result));
    if (copy == NULL || result == NULL) {
        free(copy);
        free(result);
        return 3;
    }
    for (index = 0; index < n; ++index) {
        copy[index] = parameters[index];
    }

    for (index = 0; index < n; ++index) {
        double plus;
        double minus;
        double original;

        original = copy[index];
        if (!isfinite(original + h) || !isfinite(original - h)) {
            free(copy);
            free(result);
            return 1;
        }

        copy[index] = original + h;
        plus = neuron_objective(copy, n, context);
        copy[index] = original - h;
        minus = neuron_objective(copy, n, context);
        copy[index] = original;

        if (!isfinite(plus) || !isfinite(minus)) {
            free(copy);
            free(result);
            return 2;
        }
        result[index] = (plus - minus) / (2.0 * h);
        if (!isfinite(result[index])) {
            free(copy);
            free(result);
            return 2;
        }
    }

    for (index = 0; index < n; ++index) {
        gradient[index] = result[index];
    }
    free(copy);
    free(result);
    return 0;
}

static int analytical_neuron_gradient(const double parameters[], size_t n, const NeuronContext *context, double gradient[]) {
    Activation sigmoid;
    double z;
    double prediction;
    double derivative;
    double loss_derivative;
    size_t index;

    if (parameters == NULL || context == NULL || gradient == NULL ||
        n != context->input_count + 1 || context->input == NULL) {
        return 1;
    }

    z = parameters[n - 1];
    for (index = 0; index < context->input_count; ++index) {
        z += parameters[index] * context->input[index];
    }
    if (!isfinite(z) ||
        activation_sigmoid_init(&sigmoid) != ACTIVATION_STATUS_OK ||
        activation_value(&sigmoid, z, &prediction) != ACTIVATION_STATUS_OK) {
        return 1;
    }

    derivative = prediction * (1.0 - prediction);
    loss_derivative = 2.0 * (prediction - context->target) * derivative;
    for (index = 0; index < context->input_count; ++index) {
        gradient[index] = loss_derivative * context->input[index];
    }
    gradient[n - 1] = loss_derivative;
    return 0;
}

static double absolute_error(double actual, double exact) {
    return fabs(actual - exact);
}

static double relative_error(double actual, double exact, double floor) {
    return absolute_error(actual, exact) / fmax(fabs(exact), floor);
}

int run_neuron_gradient_demo(void) {
    const double input[] = {1.0, 0.5, -1.0};
    const double weights[] = {0.8, -0.2, 0.3};
    const double bias = 0.1;
    const double target = 1.0;
    const double h = 1e-5;
    const double exact_gradient[] = {
        -0.177446917, -0.088723459, 0.177446917, -0.177446917};
    double parameters[] = {0.8, -0.2, 0.3, 0.1};
    double numerical_gradient[4];
    double analytical_gradient[4];
    NeuronContext context;
    Activation sigmoid;
    double z;
    double prediction;
    double loss;
    size_t index;

    context.input = input;
    context.input_count = 3;
    context.target = target;

    z = bias;
    for (index = 0; index < 3; ++index) {
        z += weights[index] * input[index];
    }
    if (activation_sigmoid_init(&sigmoid) != ACTIVATION_STATUS_OK ||
        activation_value(&sigmoid, z, &prediction) != ACTIVATION_STATUS_OK) {
        fputs("Failed to evaluate neuron prediction\n", stderr);
        return 1;
    }
    loss = neuron_objective(parameters, 4, &context);

    if (central_neuron_gradient(parameters, 4, h, &context,
                                numerical_gradient) != 0 ||
        analytical_neuron_gradient(parameters, 4, &context,
                                   analytical_gradient) != 0) {
        fputs("Failed to calculate neuron gradients\n", stderr);
        return 1;
    }

    printf("Neuron demo: z=%.12f, prediction=%.12f, loss=%.12f\n",
           z, prediction, loss);
    printf("index  exact   numerical   analytical   abs_error   rel_error\n");
    for (index = 0; index < 4; ++index) {
        const double abs_error =
            absolute_error(numerical_gradient[index], exact_gradient[index]);
        const double rel_error =
            relative_error(numerical_gradient[index], exact_gradient[index],
                           1e-12);
        printf("%5zu  % .9f  % .9f  % .9f  % .9e  % .9e\n",
               index, exact_gradient[index], numerical_gradient[index],
               analytical_gradient[index], abs_error, rel_error);
    }

    for (index = 0; index < 4; ++index) {
        if (!near(numerical_gradient[index], analytical_gradient[index])) {
            fprintf(stderr,
                    "Numerical and analytical gradients differ at index %zu\n",
                    index);
            return 1;
        }
    }
    if (!near(prediction, 0.622459331) ||
        !near(loss, 0.142536957)) {
        fputs("Neuron prediction or loss is outside the expected tolerance\n",
              stderr);
        return 1;
    }

    return 0;
}

int main(void) {
    return run_neuron_gradient_demo();
}

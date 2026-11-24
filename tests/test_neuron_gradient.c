#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "miniai/ml/activation/sigmoid.h"

typedef struct {
    const double *input;
    size_t input_count;
    double target;
} NeuronContext;

static int failures;
static int checks;

static int near(double actual, double expected) {
    ++checks;
    if (!isfinite(actual) || !isfinite(expected) ||
        fabs(actual - expected) >
            1e-12 + 1e-9 * fmax(fabs(actual), fabs(expected))) {
        fprintf(stderr, "FAIL: actual %.17g, expected %.17g\n",
                actual, expected);
        ++failures;
        return 0;
    }
    return 1;
}

static void expect_neuron_error(double actual, const char *message) {
    ++checks;
    if (!isnan(actual)) {
        fprintf(stderr, "FAIL: %s (actual %.17g, expected NAN)\n",
                message, actual);
        ++failures;
    }
}

static double neuron_objective(const double parameters[], size_t n,
                               void *context) {
    const NeuronContext *neuron;
    Activation sigmoid;
    double z;
    double prediction;
    double difference;
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
        if (!isfinite(parameters[index]) ||
            !isfinite(neuron->input[index])) {
            return NAN;
        }
        z += parameters[index] * neuron->input[index];
    }
    if (!isfinite(z) ||
        activation_sigmoid_init(&sigmoid) != ACTIVATION_STATUS_OK ||
        activation_value(&sigmoid, z, &prediction) != ACTIVATION_STATUS_OK ||
        !isfinite(prediction)) {
        return NAN;
    }

    difference = prediction - neuron->target;
    return difference * difference;
}

static int central_gradient(const double parameters[], size_t n, double h,
                            void *context, double gradient[]) {
    double *copy;
    double *result;
    size_t index;

    if (parameters == NULL || gradient == NULL || n == 0 ||
        !isfinite(h) || h <= 0.0) {
        return 1;
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
        if (!isfinite(parameters[index])) {
            free(copy);
            free(result);
            return 1;
        }
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

static int analytical_gradient(const double parameters[],
                               const NeuronContext *context,
                               double gradient[]) {
    Activation sigmoid;
    double z;
    double prediction;
    double loss_derivative;
    size_t index;

    if (parameters == NULL || context == NULL || gradient == NULL ||
        context->input == NULL) {
        return 1;
    }
    z = parameters[context->input_count];
    for (index = 0; index < context->input_count; ++index) {
        z += parameters[index] * context->input[index];
    }
    if (!isfinite(z) ||
        activation_sigmoid_init(&sigmoid) != ACTIVATION_STATUS_OK ||
        activation_value(&sigmoid, z, &prediction) != ACTIVATION_STATUS_OK) {
        return 1;
    }

    loss_derivative =
        2.0 * (prediction - context->target) * prediction *
        (1.0 - prediction);
    for (index = 0; index < context->input_count; ++index) {
        gradient[index] = loss_derivative * context->input[index];
    }
    gradient[context->input_count] = loss_derivative;
    return 0;
}

int main(void) {
    const double input[] = {1.0, 0.5, -1.0};
    const double parameters[] = {0.8, -0.2, 0.3, 0.1};
    const double expected_exact[] = {
        -0.17744691734927373, -0.088723458674636865,
        0.17744691734927373, -0.17744691734927373};
    double numerical[4];
    double analytical[4];
    double saved[4] = {-100.0, -100.0, -100.0, -100.0};
    double high_input[] = {100.0};
    double high_parameters[] = {100.0, 100.0};
    NeuronContext context;
    size_t index;

    context.input = input;
    context.input_count = 3;
    context.target = 1.0;

    near(neuron_objective(parameters, 4, &context), 0.14253695659655091);
    expect_neuron_error(neuron_objective(parameters, 3, &context),
                        "dimension mismatch in objective");

    if (central_gradient(parameters, 4, 1e-4, &context, numerical) != 0 ||
        analytical_gradient(parameters, &context, analytical) != 0) {
        fprintf(stderr, "FAIL: gradient calculation failed\n");
        ++failures;
    } else {
        for (index = 0; index < 4; ++index) {
            near(numerical[index], analytical[index]);
            near(numerical[index], expected_exact[index]);
        }
    }

    if (central_gradient(parameters, 4, 0.0, &context, saved) == 0) {
        fprintf(stderr, "FAIL: zero h was accepted\n");
        ++failures;
    } else {
        ++checks;
    }
    for (index = 0; index < 4; ++index) {
        ++checks;
        if (saved[index] != -100.0) {
            fprintf(stderr, "FAIL: gradient changed on invalid h\n");
            ++failures;
        }
    }

    context.input = high_input;
    context.input_count = 1;
    context.target = 1.0;
    expect_neuron_error(neuron_objective(high_parameters, 3, &context),
                        "dimension mismatch with 3 parameters");

    if (failures != 0) {
        fprintf(stderr, "%d of %d neuron gradient checks failed\n",
                failures, checks);
        return 1;
    }
    printf("%d neuron gradient checks passed\n", checks);
    return 0;
}

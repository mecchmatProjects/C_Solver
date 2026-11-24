#include <stdio.h>
#include <stddef.h>
#include <math.h>
#include "ml/activation/activation.h"

typedef struct {
    const double* input;
    double target;
    const Activation* act;
    int use_half_mse;
} NeuronObjectiveContext;

double miniai_neuron_objective(const double parameters[], size_t n, void* context);

extern ActivationStatus activation_sigmoid_init(Activation* act);

static int checks = 0;
static int failures = 0;

static void expect_near(double actual, double expected, const char* msg) {
    ++checks;
    double tol = 1e-7 * fmax(1.0, fabs(expected));
    if (!(fabs(actual - expected) <= tol)) {
        fprintf(stderr, "FAIL: %s (actual %.17g, expected %.17g)\n", msg, actual, expected);
        ++failures;
    }
}

static void expect_nan_val(double actual, const char* msg) {
    ++checks;
    if (!isnan(actual)) {
        fprintf(stderr, "FAIL: %s (expected NaN, got %.17g)\n", msg, actual);
        ++failures;
    }
}

static double reference_neuron_loss(const double x[], const double params[], size_t n,
    double target, const Activation* act, int use_half) {
    size_t num_w = n - 1;
    double z = params[num_w];
    for (size_t i = 0; i < num_w; ++i) {
        z += params[i] * x[i];
    }
    double pred = 0.0;
    activation_value(act, z, &pred);
    double d = pred - target;
    return use_half ? (0.5 * d * d) : (d * d);
}

static void test_neuron_objective(void) {
    Activation act;
    if (activation_sigmoid_init(&act) != ACTIVATION_STATUS_OK) {
        fprintf(stderr, "FAIL: cannot initialize sigmoid activation for test\n");
        ++failures;
        return;
    }

    {
        const double x[2] = { 0.8, -1.2 };
        const double params[3] = { 0.5, 0.25, -0.1 };
        const double target = 0.6;
        NeuronObjectiveContext ctx = {
            .input = x,
            .target = target,
            .act = &act,
            .use_half_mse = 1
        };

        double actual = miniai_neuron_objective(params, 3, &ctx);
        double expected = reference_neuron_loss(x, params, 3, target, &act, 1);
        expect_near(actual, expected, "Objective matches neuron_demo loss for valid inputs");
    }

    /* 2. Перевірка градієнта центральною різницею (похибка O(h^2)) */
    {
        const double x[2] = { 1.0, 2.0 };
        double params[3] = { 0.2, -0.4, 0.05 };
        const double target = 0.75;
        NeuronObjectiveContext ctx = {
            .input = x,
            .target = target,
            .act = &act,
            .use_half_mse = 1
        };

        const double h = 1e-6;
        params[0] += h;
        double f_plus = miniai_neuron_objective(params, 3, &ctx);
        params[0] -= 2.0 * h;
        double f_minus = miniai_neuron_objective(params, 3, &ctx);
        params[0] += h;

        double num_grad_w0 = (f_plus - f_minus) / (2.0 * h);
        /* Очікуємо скінченне число без NaN/Inf */
        ++checks;
        if (!isfinite(num_grad_w0)) {
            fprintf(stderr, "FAIL: numerical gradient is not finite (%.17g)\n", num_grad_w0);
            ++failures;
        }
    }

    /* 3. Граничний випадок: n не відповідає числу weights + 1 (наприклад, n < 2) */
    {
        const double x[1] = { 1.0 };
        const double params[1] = { 0.5 };
        NeuronObjectiveContext ctx = {
            .input = x,
            .target = 0.0,
            .act = &act,
            .use_half_mse = 1
        };
        expect_nan_val(miniai_neuron_objective(params, 1, &ctx), "Invalid n=1 (no bias/weights pair)");
        expect_nan_val(miniai_neuron_objective(params, 0, &ctx), "Invalid n=0");
    }

    /* 4. Граничний випадок: невалідний контекст (NULL або відсутні поля) */
    {
        const double params[2] = { 0.5, 0.1 };
        expect_nan_val(miniai_neuron_objective(params, 2, NULL), "NULL context returns NaN");

        NeuronObjectiveContext bad_ctx = {
            .input = NULL,
            .target = 1.0,
            .act = &act,
            .use_half_mse = 1
        };
        expect_nan_val(miniai_neuron_objective(params, 2, &bad_ctx), "NULL input in context returns NaN");
    }
}

int main(void) {
    test_neuron_objective();

    if (failures > 0) {
        fprintf(stderr, "FAILURE: %d of %d checks failed.\n", failures, checks);
        return 1;
    }

    printf("SUCCESS: All %d checks passed.\n", checks);
    return 0;
}
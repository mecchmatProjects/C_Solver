#include <stdio.h>
#include <stddef.h>

typedef struct Activation Activation;
typedef struct {
    const double* input;
    double target;
    const Activation* act;
    int use_half_mse;
} NeuronObjectiveContext;

double miniai_neuron_objective(const double parameters[], size_t n, void* context);

/* Приклад локального виклику для заданих x, target та параметрів [w0, w1, bias] */
int run_neuron_gradient_demo(const Activation* act) {
    const double x[2] = { 1.5, -2.0 };
    double params[3] = { 0.4, -0.3, 0.1 }; /* w0, w1, bias -> n = 3 (2 ваги + 1 bias) */
    const size_t n = 3;

    NeuronObjectiveContext ctx = {
        .input = x,
        .target = 1.0,
        .act = act,
        .use_half_mse = 1
    };

    double base_loss = miniai_neuron_objective(params, n, &ctx);
    printf("Base objective loss: %.10f\n", base_loss);

    const double eps = 1e-6;
    for (size_t i = 0; i < n; ++i) {
        double orig = params[i];

        params[i] = orig + eps;
        double loss_plus = miniai_neuron_objective(params, n, &ctx);

        params[i] = orig - eps;
        double loss_minus = miniai_neuron_objective(params, n, &ctx);

        params[i] = orig;

        double grad_num = (loss_plus - loss_minus) / (2.0 * eps);
        printf("d(loss)/d(param[%zu]) [central diff]: %.10f\n", i, grad_num);
    }

    return 0;
}
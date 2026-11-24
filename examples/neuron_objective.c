#include <stddef.h>
#include <math.h>
#include "ml/activation/activation.h"

//Лінійна комбінація (pre-activation):$$z = \sum_{j=0}^{k-1} w_j x_j + b$$
//Активація та передбачення:$$\hat{y} = a(z)$$
//Функція втрат (MSE за замовчуванням, якщо інше не задано в контексті):$$\mathcal{L}(\theta) = \frac{1}{2}(\hat{y} - y_{\text{true}})^2 \quad \text{або} \quad (\hat{y} - y_{\text{true}})^2$$

typedef struct {
    const double* input;       /* Вектор ознак довжини num_weights (n - 1) */
    double target;             /* Цільове значення (y_true) */
    const Activation* act;     /* Вказівник на ініціалізовану активацію */
    int use_half_mse;          /* 1 -> 0.5 * (pred - target)^2, 0 -> (pred - target)^2 */
} NeuronObjectiveContext;

double miniai_neuron_objective(const double parameters[], size_t n, void* context) {
    if (parameters == NULL || context == NULL || n < 2) {
        return NAN;
    }

    const NeuronObjectiveContext* ctx = (const NeuronObjectiveContext*)context;
    size_t num_weights = n - 1;

    if (ctx->input == NULL || ctx->act == NULL) {
        return NAN;
    }

    /* 1. Обчислення зваженої суми + bias: parameters[0..num_weights-1] і parameters[num_weights] */
    double z = parameters[num_weights];
    for (size_t i = 0; i < num_weights; ++i) {
        if (!isfinite(parameters[i]) || !isfinite(ctx->input[i])) {
            return NAN;
        }
        z += parameters[i] * ctx->input[i];
    }

    if (!isfinite(parameters[num_weights]) || !isfinite(ctx->target)) {
        return NAN;
    }

    /* 2. Активація через чинний Activation API */
    double pred = 0.0;
    ActivationStatus st = activation_value(ctx->act, z, &pred);
    if (st != ACTIVATION_STATUS_OK || !isfinite(pred)) {
        return NAN;
    }

    /* 3. Втрати */
    double diff = pred - ctx->target;
    double loss = diff * diff;
    if (ctx->use_half_mse) {
        loss *= 0.5;
    }

    return loss;
}
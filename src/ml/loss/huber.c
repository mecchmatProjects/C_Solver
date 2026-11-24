#include <math.h>

#include "miniai/ml/loss/losses.h"

#include <math.h>

double miniai_huber_loss(double prediction, double target, double delta) {
    double error;
    double absolute_error;

    if (!isfinite(prediction) || !isfinite(target) || !isfinite(delta) ||
        delta <= 0.0) {
        return NAN;
    }
/**
 * @brief Обчислює похідну функції втрат Гьюбера за похибкою (prediction - target).
 *
 * Математична постановка:
 *   e, якщо |e| <= delta
 *   delta * sign(e), інакше
 *
 * @param prediction Передбачене значення моделі
 * @param target Цільове значення
 * @param delta Параметр порогу дельта (delta > 0)
 * @return double Значення похідної
 */
double miniai_huber_loss_derivative(double prediction, double target, double delta) {
    // Якщо delta від'ємна або нульова, зазвичай повертають 0 або обробляють як виняток
    if (delta <= 0.0) {
        return 0.0;
    }

    double e = prediction - target;

    if (fabs(e) <= delta) {
        return e;
    }
    else {
        // sign(e): якщо e > 0, то 1.0; якщо e < 0, то -1.0; якщо e == 0, то 0.0
        double sign_e = (e > 0.0) ? 1.0 : ((e < 0.0) ? -1.0 : 0.0);
        return delta * sign_e;
    }
}

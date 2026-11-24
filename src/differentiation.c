#include "miniai/differentiation.h"

#include <math.h>

/* 1. Публічна валідація кроку: відсіюємо 0, від'ємні числа, NAN та +/-INFINITY */
int miniai_is_valid_step(double h) {
    return (isfinite(h) && h > 0.0) ? 1 : 0;
}

/* 2. Внутрішній helper: перевірка callback-вказівника, точки x та кроку h для скалярної функції */
static int miniai_validate_scalar_params(miniai_scalar_function_with_context f, double x, double h) {
    if (f == NULL) {
        return 0;
    }
    if (!isfinite(x)) {
        return 0;
    }
    if (!miniai_is_valid_step(h)) {
        return 0;
    }
    return 1;
}

/* 3. Внутрішній helper: перевірка вказівників, розмірності n та кроку h для вектора градієнта */
static int miniai_validate_gradient_params(
    miniai_objective_function f,
    const double *x,
    size_t n,
    double h,
    const double *grad_out
) {
    if (f == NULL || x == NULL || grad_out == NULL) {
        return 0;
    }
    if (n == 0U) {
        return 0;
    }
    if (!miniai_is_valid_step(h)) {
        return 0;
    }
    return 1;
}

/* 4. Безпечне обчислення похідної: спершу валідація, потім формула центральної різниці */
double miniai_differentiate_scalar_checked(
    miniai_scalar_function_with_context f,
    double x,
    double h,
    void *user_data
) {
    if (!miniai_validate_scalar_params(f, x, h)) {
        return NAN;
    }
    return (f(x + h, user_data) - f(x - h, user_data)) / (2.0 * h);
}

/* 5. Безпечна перевірка виклику градієнта без зміни вихідного масиву у разі помилки */
int miniai_gradient_checked(
    miniai_objective_function f,
    const double *x,
    size_t n,
    double h,
    double *grad_out,
    void *user_data
) {
    if (!miniai_validate_gradient_params(f, x, n, h, grad_out)) {
        return -1;
    }
    (void)f;
    (void)x;
    (void)n;
    (void)h;
    (void)grad_out;
    (void)user_data;
    return 0;
}
double miniai_derivative_central(miniai_scalar_function f, double x, double h) {
    double f_plus;
    double f_minus;
    double result;

    if (f == NULL || !isfinite(h) || h <= 0.0) {
        return NAN;
    }
    if (!isfinite(x + h) || !isfinite(x - h)) {
        return NAN;
    }

    f_plus = f(x + h);
    f_minus = f(x - h);
    if (!isfinite(f_plus) || !isfinite(f_minus)) {
        return NAN;
    }

    result = (f_plus - f_minus) / 2.0 / h;
    return isfinite(result) ? result : NAN;
}

double miniai_derivative_backward(miniai_scalar_function f,
                                  double x, double h) {
    if (f == NULL || !isfinite(x) || !isfinite(h) || h <= 0.0) {
        return NAN;
    }

    double previous_x = x - h;

    if (!isfinite(previous_x)) {
        return NAN;
    }

    double value = f(x);
    double previous_value = f(previous_x);

    if (!isfinite(value) || !isfinite(previous_value)) {
        return NAN;
    }

    double derivative = (value - previous_value) / h;

    if (!isfinite(derivative)) {
        return NAN;
    }

    return derivative;
}

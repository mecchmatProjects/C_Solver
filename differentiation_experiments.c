#include "miniai/differentiation_experiments.h"
#include <math.h>

int miniai_step_sweep(miniai_scalar_function f, double exact, double x, 
                      const double steps[], size_t n, double errors[], 
                      size_t *best_index) {
    
    //Перевірка вказівників
    if (f == NULL || steps == NULL || errors == NULL || best_index == NULL) {
        return MINIAI_ERR_NULL_PTR;
    }
    //Перевірка розмірності
    if (n == 0) {
        return MINIAI_ERR_INVALID_ARG;
    }

    size_t best_idx = 0;
    double min_error = HUGE_VAL;
    int valid_steps_found = 0;

    for (size_t i = 0; i < n; ++i) {
        double h = steps[i];

        // h має бути > 0, і не бути NaN/Inf
        if (h <= 0.0 || isnan(h) || isinf(h)) {
            errors[i] = NAN;
            continue;
        }

        // Формула центральної різниці
        double f_plus  = f(x + h);
        double f_minus = f(x - h);

        // Перевірка f(x) на NaN/Inf
        if (isnan(f_plus) || isinf(f_plus) || isnan(f_minus) || isinf(f_minus)) {
            errors[i] = NAN;
            continue;
        }

        double approx = (f_plus - f_minus) / (2.0 * h);

        // Абсолютна похибка
        double err = fabs(approx - exact);
        errors[i] = err;
        valid_steps_found = 1;

        // Пошук мінімуму
        if (err < min_error) {
            min_error = err;
            best_idx = i;
        }
    }

    // 3апис результату
    *best_index = best_idx;
    
    if (!valid_steps_found) {
        return MINIAI_ERR_NUMERIC;
    }

    return MINIAI_OK;
}
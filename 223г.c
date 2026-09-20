#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <float.h>

static bool is_zero_erelu(double x) {
    return fabs(x) < 1e-9;
}

// Функція eReLu (пункт г)
double eReLu(double a, double x) {
    if (x < 0.0) {
        return a * (exp(x) - 1.0);
    } else {
        return 0.0;
    }
}

// Похідна eReLu
double eReLuDerivative(double a, double x) {
    if (is_zero_erelu(x)) {
        return DBL_MAX; // за умовою нескінченність позначається через DBL_MAX
    } else if (x < 0.0) {
        return a * exp(x);
    } else {
        return 0.0;
    }
}

// Автоматичний тест
int test_eReLu(void) {
    double a = 2.0;

    // 1. x = -1.0 -> f(-1) = 2*(exp(-1) - 1), f'(-1) = 2*exp(-1)
    double exp_val = a * (exp(-1.0) - 1.0);
    double exp_deriv = a * exp(-1.0);
    if (!is_zero_erelu(eReLu(a, -1.0) - exp_val)) return 1;
    if (!is_zero_erelu(eReLuDerivative(a, -1.0) - exp_deriv)) return 1;

    // 2. x = 0.0 -> f(0) = 0, f'(0) = DBL_MAX
    if (!is_zero_erelu(eReLu(a, 0.0) - 0.0)) return 1;
    if (eReLuDerivative(a, 0.0) != DBL_MAX) return 1;

    // 3. x = 1.0 -> f(1) = 0, f'(1) = 0
    if (!is_zero_erelu(eReLu(a, 1.0) - 0.0)) return 1;
    if (!is_zero_erelu(eReLuDerivative(a, 1.0) - 0.0)) return 1;

    return 0;
}
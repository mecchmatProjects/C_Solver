#include <stdio.h>
#include <math.h>
#include <float.h>

double soft_exponential(double a, double x) {
    if (a < 0.0) {
        return -log(1.0 - a * (x + a)) / a;
    } else if (a == 0.0) {
        return x;
    } else {
        return (exp(a * x) - 1.0) / a + a;
    }
}

double soft_exponential_deriv(double a, double x) {
    if (a < 0.0) {
        double denom = 1.0 - a * (x + a);
        if (denom <= 0.0) return DBL_MAX; 
        return 1.0 / denom;
    } else if (a == 0.0) {
        return 1.0;
    } else {
        return exp(a * x);
    }
}

int test_soft_exponential(void) {
    double x = 1.5;
    double eps = 1e-6;

    double a1 = -0.5;
    double exp_val1 = 2.0 * log(1.5);
    double exp_deriv1 = 1.0 / 1.5;
    if (fabs(soft_exponential(a1, x) - exp_val1) > eps) return 1;
    if (fabs(soft_exponential_deriv(a1, x) - exp_deriv1) > eps) return 1;

    double a2 = 0.0;
    double exp_val2 = 1.5;
    double exp_deriv2 = 1.0;
    if (fabs(soft_exponential(a2, x) - exp_val2) > eps) return 1;
    if (fabs(soft_exponential_deriv(a2, x) - exp_deriv2) > eps) return 1;

    double a3 = 0.5;
    double exp_val3 = 2.0 * (exp(0.75) - 1.0) + 0.5;
    double exp_deriv3 = exp(0.75);
    if (fabs(soft_exponential(a3, x) - exp_val3) > eps) return 1;
    if (fabs(soft_exponential_deriv(a3, x) - exp_deriv3) > eps) return 1;

    return 0;
}

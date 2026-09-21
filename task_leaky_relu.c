#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <float.h>

static bool is_zero_leaky(double x) {
    return fabs(x) < 1e-9;
}

// Завдання 23 (пункт в): leakyReLu(x, a)
double leakyRelu(double x, double a) {
    if (x < 0.0) {
        return a * x;
    }
    return 0.0;
}

// Похідна для пункту в
double leakyReluDerivative(double x, double a) {
    if (is_zero_leaky(x)) {
        return DBL_MAX; // нескінченність у точці зламу
    }
    if (x < 0.0) {
        return a;
    }
    return 0.0;
}

int test_leakyRelu(void) {
    double a = 0.1;

    // x < 0: f(-2) = -0.2, f'(-2) = 0.1
    if (fabs(leakyRelu(-2.0, a) - (-0.2)) > 1e-9) return 1;
    if (fabs(leakyReluDerivative(-2.0, a) - a) > 1e-9) return 1;

    // x = 0: f(0) = 0.0, f'(0) = DBL_MAX
    if (fabs(leakyRelu(0.0, a) - 0.0) > 1e-9) return 1;
    if (leakyReluDerivative(0.0, a) != DBL_MAX) return 1;

    // x > 0: f(2) = 0.0, f'(2) = 0.0
    if (fabs(leakyRelu(2.0, a) - 0.0) > 1e-9) return 1;
    if (fabs(leakyReluDerivative(2.0, a) - 0.0) > 1e-9) return 1;

    return 0; 
}

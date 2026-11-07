//
// Created by Katya on 12.09.2026.
//
// task 2.23 (a)
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>

static bool is_zero(double x) {
    return fabs(x) < 1e-9;
}

// ONESTEP
double onestep(double x) {
    if (x >= 0) {
        return 1;
    } else {
        return 0;
    }
}
double onestep_derivative(double x) {
    if (is_zero(x)) {
        return DBL_MAX;
    }
    return 0;
}

int test_onestep() {
    if (!is_zero(onestep(-1))) {
        printf("Test onestep for -1 is failed\n");
        return 1;
    }
    if (!is_zero(onestep(0)-1)) {
        printf("Test onestep for 0 is failed\n");
        return 1;
    }
    if (!is_zero(onestep(2)-1)) {
        printf("Test onestep for 2 is failed\n");
        return 1;
    }
    return 0;
}

// RELU
double ReLu(double x) {
    if (x < 0.0) {
        return 0.0;
    } else {
        return x;
    }
}

double ReLu_derivative(double x) {
    if (is_zero(x)) {
        return DBL_MAX;
    } else if (x > 0.0) {
        return 1.0;
    } else {
        return 0.0;
    }
}

int test_Relu(void) {
    if (fabs(ReLu(-2.0) - 0.0) >= 1e-9) return 1;
    if (fabs(ReLu(0.0) - 0.0) >= 1e-9) return 1;
    if (fabs(ReLu(2.0) - 2.0) >= 1e-9) return 1;

    if (fabs(ReLu_derivative(-2.0) - 0.0) >= 1e-9) return 1;
    if (fabs(ReLu_derivative(2.0) - 1.0) >= 1e-9) return 1;
    if (ReLu_derivative(0.0) != DBL_MAX) return 1;

    return 0;
}

// LEAKY RELU
double leakyRelu(double x, double a) {
    if (x < 0.0) {
        return a * x;
    }
    return 0.0;
}

// Похідна для пункту в
double leakyReluDerivative(double x, double a) {
    if (is_zero(x)) {
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

// E RELU
double eReLu(double a, double x) {
    if (x < 0.0) {
        return a * (exp(x) - 1.0);
    } else {
        return 0.0;
    }
}

// Похідна eReLu
double eReLuDerivative(double a, double x) {
    if (is_zero(x)) {
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
    if (!is_zero(eReLu(a, -1.0) - exp_val)) return 1;
    if (!is_zero(eReLuDerivative(a, -1.0) - exp_deriv)) return 1;

    // 2. x = 0.0 -> f(0) = 0, f'(0) = DBL_MAX
    if (!is_zero(eReLu(a, 0.0) - 0.0)) return 1;
    if (eReLuDerivative(a, 0.0) != DBL_MAX) return 1;

    // 3. x = 1.0 -> f(1) = 0, f'(1) = 0
    if (!is_zero(eReLu(a, 1.0) - 0.0)) return 1;
    if (!is_zero(eReLuDerivative(a, 1.0) - 0.0)) return 1;

    return 0;
}

// S RELU
double sRelu(double tl, double tr, double al, double ar, double x) {
    if (x <= tl) {
        return tl + al * (x - tl);
    }
    else if (x < tr) {
        return 0;
    }
    else {
        return tr + ar * (x - tr);
    }
}

double sRelu_derivative(double tl, double tr, double al, double ar, double x) {
    if (is_zero(x - tl) || is_zero(x - tr)) {
        return DBL_MAX;
    }
    else if (x < tl) {
        return al;
    }
    else if (x < tr) {
        return 0;
    }
    else {
        return ar;
    }
}

int test_sRelu(void) {
    double tl = -1.0;
    double tr = 1.0;
    double al = 0.2;
    double ar = 0.3;

    if (!is_zero(sRelu(tl, tr, al, ar, -2.0) - (-1.2))) {
        printf("Test sRelu for -2 is failed\n");
        return 1;
    }

    if (!is_zero(sRelu(tl, tr, al, ar, 0.0))) {
        printf("Test sRelu for 0 is failed\n");
        return 1;
    }

    if (!is_zero(sRelu(tl, tr, al, ar, 2.0) - 1.3)) {
        printf("Test sRelu for 2 is failed\n");
        return 1;
    }

    if (!is_zero(sRelu_derivative(tl, tr, al, ar, -2.0) - al)) {
        printf("Test sRelu derivative for -2 is failed\n");
        return 1;
    }

    if (!is_zero(sRelu_derivative(tl, tr, al, ar, 0.0))) {
        printf("Test sRelu derivative for 0 is failed\n");
        return 1;
    }

    if (!is_zero(sRelu_derivative(tl, tr, al, ar, 2.0) - ar)) {
        printf("Test sRelu derivative for 2 is failed\n");
        return 1;
    }

    return 0;
}

// SOFT EXPONENTIAL
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

// SINC
double sinc(double x) {  //Функція sinc
    if (is_zero(x)) {
        return 1.0;
    } else {
        return sin(x) / x;
    }
}

double sinc_derivative(double x) {  //Похідна функції sinc
    if (is_zero(x)) {
        return 0.0;
    } else {
        return (x * cos(x) - sin(x)) / (x * x);
    }
}

int test_sinc(void) { //Тест для функції sinc
    if (!is_zero(sinc(0) - 1.0)) {
        printf("Test sinc for 0 is failed\n");
        return 1;
    }
    if (!is_zero(sinc(1.0) - sin(1.0))) {
        printf("Test sinc for 1 is failed\n");
        return 1;
    }
    return 0;
}

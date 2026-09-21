#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <float.h>

double leakyRelu(double x, double a) {
    if (x < 0) {
        return a * x;
    }
    return x;
}

double leakyReluDerivative(double x, double a) {
    if (x == 0.0) {
        return DBL_MAX;
    }
    if (x < 0) {
        return a;
    }
    return 0.0;
}

int test_leakyRelu(void) {
    double a = 0.1;
    if (fabs(leakyRelu(-2.0, a) - (-0.2)) > 1e-9) return 1;
    if (fabs(leakyReluDerivative(-2.0, a) - a) > 1e-9) return 1;
    if (fabs(leakyRelu(2.0, a) - 2.0) > 1e-9) return 1;
    if (fabs(leakyReluDerivative(2.0, a) - 0.0) > 1e-9) return 1;
    if (fabs(leakyReluDerivative(0.0, a) - DBL_MAX) > 1e-9) return 1;
    return 0;
}
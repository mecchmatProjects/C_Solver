#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>

bool is_zero(double x) {
    return fabs(x) < 1e-9;
}


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

int test_sRelu() {
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

int main() {
    if (test_sRelu() == 0) {
        printf("Test passed successfully.\n");
    }
    else {
        printf("Test failed.\n");
    }

    return 0;
}
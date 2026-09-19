#include <stdio.h>
#include <math.h>
#include <stdbool.h>

static bool is_zero_softsign(double x) {
    return fabs(x) < 1e-9;
}

double softSign(double x) { 
    return x / (1.0 + fabs(x)); 
}

double softSign_derivative(double x) { 
    double d = 1.0 + fabs(x); 
    return 1.0 / (d * d); 
}

int test_softSign(void) {
    if (!is_zero_softsign(softSign(0.0) - 0.0)) {
        printf("Test softSign(0) failed\n");
        return 1;
    }
    if (!is_zero_softsign(softSign_derivative(0.0) - 1.0)) {
        printf("Test softSign_derivative(0) failed\n");
        return 1;
    }

    if (!is_zero_softsign(softSign(1.0) - 0.5)) {
        printf("Test softSign(1) failed\n");
        return 1;
    }
    if (!is_zero_softsign(softSign_derivative(1.0) - 0.25)) {
        printf("Test softSign_derivative(1) failed\n");
        return 1;
    }

    return 0; 
}

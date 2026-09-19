#include <stdio.h>
#include <math.h>
#include <stdbool.h>

bool is_zero(double x) {
    return fabs(x) < 1e-9;
}

double softPlus(double x) {
    if (x > 20.0) {
        return x; 
    }
    return log(1.0 + exp(x));
}

double softPlus_derivative(double x) {
    if (x > 20.0) {
        return 1.0; 
    }
    if (x < -20.0) {
        return 0.0;
    }
    
    double exp_x = exp(x);
    return exp_x / (1.0 + exp_x);
}

double numerical_derivative(double x, double h) {
    return (softPlus(x + h) - softPlus(x - h)) / (2.0 * h);
}

int test_softPlus() {
    if (!is_zero(softPlus(0.0) - log(2.0))) {
        printf("Test failed: softPlus(0.0) should be ln(2)\n");
        return 1;
    }
    
    if (!is_zero(softPlus(25.0) - 25.0)) {
        printf("Test failed: softPlus(25.0) should be approx 25.0\n");
        return 1;
    }
    
    return 0;
}

int test_softPlus_derivative() {
    if (!is_zero(softPlus_derivative(0.0) - 0.5)) {
        printf("Test failed: softPlus_derivative(0.0) should be 0.5\n");
        return 1;
    }

    double h = 1e-5;
    
    if (!is_zero(softPlus_derivative(1.0) - numerical_derivative(1.0, h))) {
        printf("Test failed: softPlus_derivative(1.0) does not match numerical derivative\n");
        return 1;
    }

    if (!is_zero(softPlus_derivative(-1.0) - numerical_derivative(-1.0, h))) {
        printf("Test failed: softPlus_derivative(-1.0) does not match numerical derivative\n");
        return 1;
    }

    return 0;
}

int main() {
    if (test_softPlus() == 0 && test_softPlus_derivative() == 0) {
        printf("All tests passed successfully!\n");
    } else {
        printf("Some tests failed. Check the output above.\n");
    }
    
    return 0;
}

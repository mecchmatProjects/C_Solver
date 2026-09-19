#include <stdio.h>
#include <math.h>
#include <stdbool.h>



// check if a floating-point number is practically zero
bool is_zero(double x) {
    return fabs(x) < 1e-9;
}

// main function
double sigmweight(double x) {
    return x / (1.0 + exp(-x));
}

double sigmweight_derivative(double x) {
    double exp_nx = exp(-x);
    double denom = 1.0 + exp_nx;
    return (1.0 + (x + 1.0) * exp_nx) / (denom * denom);
}

double numerical_derivative(double x, double h) {
    return (sigmweight(x + h) - sigmweight(x - h)) / (2.0 * h);
}



// TESTS

// Test the main function
int test_sigmweight() {
    if (!is_zero(sigmweight(0.0))) {
        printf("Test failed: sigmweight(0.0) should be 0.0\n");
        return 1;
    }

    if (!is_zero(sigmweight(1.0) - (1.0 / (1.0 + exp(-1.0))))) {
        printf("Test failed: sigmweight(1.0) is incorrect\n");
        return 1;
    }

    if (!is_zero(sigmweight(-1.0) - (-1.0 / (1.0 + exp(1.0))))) {
        printf("Test failed: sigmweight(-1.0) is incorrect\n");
        return 1;
    }

    return 0;
}

// Test the derivative
int test_sigmweight_derivative() {
    double h = 1e-5;
    
    if (!is_zero(sigmweight_derivative(0.0) - 0.5)) {
        printf("Test failed: sigmweight_derivative(0.0) should be 0.5\n");
        return 1;
    }

    if (!is_zero(sigmweight_derivative(1.0) - numerical_derivative(1.0, h))) {
        printf("Test failed: sigmweight_derivative(1.0) does not match numerical derivative\n");
        return 1;
    }

    if (!is_zero(sigmweight_derivative(-1.0) - numerical_derivative(-1.0, h))) {
        printf("Test failed: sigmweight_derivative(-1.0) does not match numerical derivative\n");
        return 1;
    }

    return 0;
}

int main() {
    // Запускаємо обидва тести
    if (test_sigmweight() == 0 && test_sigmweight_derivative() == 0) {
        printf("All tests passed successfully!\n");
    } else {
        printf("Some tests failed. Check the output above.\n");
    }
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
bool iszero(double x) {
    return fabs(x) < 1e-9;
}
double soft_sign(double x) {
    return x/(1+fabs(x));
}
double soft_sign_derivative(double x) {
    const double h = 1e-5;
    return (soft_sign(x+h)-soft_sign(x-h))/(2*h);
}
int test_soft_sign() {
    if (!iszero(soft_sign(0))) {
        printf("test for soft_sign has failed\n");
        return 1;
    }
    if (!iszero(soft_sign(1)-0.5)) {
        printf("test for soft_sign has failed\n");
        return 1;
    }
    if (!iszero(soft_sign(-1)+0.5)) {
        printf("test for soft_sign has failed\n");
        return 1;
    }
    return 0;
}
int derivative_test_soft_sign() {
    if (!iszero(soft_sign_derivative(-1))) {
        printf("test for soft_sign has failed\n");
        return 1;
    }
    if (!iszero(soft_sign_derivative(0)-1)) {
        printf("test for soft_sign has failed\n");
        return 1;
    }
    if (!iszero(soft_sign_derivative(1)-0.5)) {
        printf("test for soft_sign has failed\n");
        return 1;
    }
    return 0;
}


double invsqrt(double x, double alpha){
    if (alpha*x*x < -1) {
        return NAN;
    }
    return x/sqrt(1+alpha*x*x);
}
    
double invsqrt_derivative(double x, double alpha) {
    if (alpha*x*x < -1) {
        return NAN;
    }
    double y = pow(1+alpha*x*x, 3);
    return 1/sqrt(y);
}

bool iszero(double x) {
    return fabs(x) < 1e-9;
}
///Tests
int tests() {
    printf("tests ...\n");
    if (!iszero(invsqrt(0.0, 0.0))) {
        printf("invsqrt(0.0, 0.0) != 0\n");
        return 1;
    }
    if (!iszero(invsqrt(1.0, 3.0)-0.5)) {
        printf("invsqrt(1.0, 3.0) != 0.5\n");
        return 1;
    }
    if (!isnan(invsqrt(-1.0, -5.0))) {
        printf("invsqrt(-1.0, -5.0) != nan\n");
        return 1;
    }
    if (!iszero(invsqrt_derivative(0.0, 0.0)-1.0)) {
        printf("invsqrt_derivative(0.0, 0.0) != 1\n");
    }
    if (!isnan(invsqrt_derivative(1.0, -3.0))) {}
    printf("tests are successful\n");
    return 0;
}

int main() {
    double x, alpha;
    tests();
    printf("input x and alpha: ");
    scanf("%lf %lf", &x, &alpha);
    double i = invsqrt(x, alpha);
    double j = invsqrt_derivative(x, alpha);
    printf("invsqrt(%lf, %lf) = %lf\n", x, alpha, i);
    printf("invsqrt_derivative(%lf, %lf) = %lf\n", x, alpha, j);
}

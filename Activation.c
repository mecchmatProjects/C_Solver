#define _USE_MATH_DEFINES
#include 
#include 
#include 

bool is_zero(double x) {
    return fabs(x) < 1e-9;
}

// 1. 

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

double numerical_derivative_softPlus(double x, double h) {
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
    if (!is_zero(softPlus_derivative(1.0) - numerical_derivative_softPlus(1.0, h))) {
        printf("Test failed: softPlus_derivative(1.0) does not match numerical derivative\n");
        return 1;
    }
    if (!is_zero(softPlus_derivative(-1.0) - numerical_derivative_softPlus(-1.0, h))) {
        printf("Test failed: softPlus_derivative(-1.0) does not match numerical derivative\n");
        return 1; 
    }
    return 0;
}


// 2. 

double arctan(double x) {
    double epsilon = 1e-9;
    double result = 0.0;
    double term = x;
    int n = 1;
    while (fabs(term) > epsilon) {
        result += term;
        term *= -x * x * (2 * n - 1) / (2 * n + 1);
        n++;
    }
    return result;
}

double arctan_derivative(double x) {
    return 1.0 / (1.0 + x * x);
}

int test_arctan() {
    if(!is_zero(arctan(0.0))) {
        printf("Test failed: arctan(0.0) should be 0.0\n");
        return 1;
    }
    if(!is_zero(arctan(1.0) - M_PI/4)) {
        printf("Test failed: arctan(1.0) should be approximately π/4\n");
        return 1; 
    }
    return 0;
}

int test_arctan_derivative() {
    if(!is_zero(arctan_derivative(0.0) - 1.0)) {
        printf("Test failed: arctan_derivative(0.0) should be 1.0\n");
        return 1;
    }
    if(!is_zero(arctan_derivative(1.0) - 0.5)) {
        printf("Test failed: arctan_derivative(1.0) should be approximately 0.5\n");
        return 1;
    }
    if(!is_zero(arctan_derivative(-1.0) - 0.5)) {
        printf("Test failed: arctan_derivative(-1.0) should be approximately 0.5\n");
        return 1; 
    }
    return 0;
}


// 3.

double sigmweight(double x) {
    return x / (1.0 + exp(-x));
}

double sigmweight_derivative(double x) {
    double exp_nx = exp(-x);
    double denom = 1.0 + exp_nx;
    return (1.0 + (x + 1.0) * exp_nx) / (denom * denom);
}

double numerical_derivative_sigmweight(double x, double h) {
    return (sigmweight(x + h) - sigmweight(x - h)) / (2.0 * h);
}

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

int test_sigmweight_derivative() {
    double h = 1e-5;
    if (!is_zero(sigmweight_derivative(0.0) - 0.5)) {
        printf("Test failed: sigmweight_derivative(0.0) should be 0.5\n");
        return 1;
    }
    if (!is_zero(sigmweight_derivative(1.0) - numerical_derivative_sigmweight(1.0, h))) {
        printf("Test failed: sigmweight_derivative(1.0) does not match numerical derivative\n");
        return 1;
    }
    if (!is_zero(sigmweight_derivative(-1.0) - numerical_derivative_sigmweight(-1.0, h))) {
        printf("Test failed: sigmweight_derivative(-1.0) does not match numerical derivative\n");
        return 1;
    }
    return 0;
}

// 4.

double soft_sign(double x) {
    return x/(1+fabs(x));
}

double soft_sign_derivative(double x) {
    const double h = 1e-5;
    return (soft_sign(x+h)-soft_sign(x-h))/(2*h);
}

int test_soft_sign() {
    if (!is_zero(soft_sign(0))) {
        printf("test for soft_sign has failed\n");
        return 1;
    }
    if (!is_zero(soft_sign(1)-0.5)) {
        printf("test for soft_sign has failed\n");
        return 1;
    }
    if (!is_zero(soft_sign(-1)+0.5)) {
        printf("test for soft_sign has failed\n");
        return 1;
    }
    return 0;
}

int derivative_test_soft_sign() {
    if (!is_zero(soft_sign_derivative(-1))) {
        printf("test for soft_sign derivative has failed\n");
        return 1;
    }
    if (!is_zero(soft_sign_derivative(0)-1)) {
        printf("test for soft_sign derivative has failed\n");
        return 1;
    }
    if (!is_zero(soft_sign_derivative(1)-0.5)) {
        printf("test for soft_sign derivative has failed\n");
        return 1;
    }
    return 0;
}


// 5. 

double invsqrt(double x, double alpha) {
    return x / sqrt(1.0 + alpha * x * x);
}

double invsqrt_derivative(double x, double alpha) {
    double base = 1.0 + alpha * x * x;
    return 1.0 / (base * sqrt(base));
}

int tests() {
    printf("tests for invsqrt...\n");
    if (!is_zero(invsqrt(0.0, 0.0))) {
        printf("invsqrt(0.0, 0.0) != 0\n");
        return 1;
    }
    if (!is_zero(invsqrt(1.0, 3.0)-0.5)) {
        printf("invsqrt(1.0, 3.0) != 0.5\n");
        return 1;
    }
    if (!isnan(invsqrt(-1.0, -5.0))) {
        printf("invsqrt(-1.0, -5.0) != nan\n");
        return 1;
    }
    if (!is_zero(invsqrt_derivative(0.0, 0.0)-1.0)) {
        printf("invsqrt_derivative(0.0, 0.0) != 1\n");
        return 1;
    }
    if (!isnan(invsqrt_derivative(1.0, -3.0))) {
    }
    printf("tests for invsqrt are successful\n");
    return 0;
}


// 6. 

double bent(double x) {
    return (sqrt(x * x + 1.0) - 1.0) / 2.0 + x;
}

double bent_derivative(double x) {
    return x / (2.0 * sqrt(x * x + 1.0)) + 1.0;
}

int test_bent() {
    if (!is_zero(bent(0.0))) {
        printf("Test failed at x = 0.0\n"); return 1;
    }
    if (!is_zero(bent(1.0) - ((sqrt(2.0) - 1.0) / 2.0 + 1.0))) {
        printf("Test failed at x = 1.0\n"); return 1;
    }
    if (!is_zero(bent(-1.0) - ((sqrt(2.0) - 1.0) / 2.0 - 1.0))) {
        printf("Test failed at x = -1.0\n"); return 1;
    }
    if (!is_zero(bent(0.5) - ((sqrt(1.25) - 1.0) / 2.0 + 0.5))) {
        printf("Test failed at x = 0.5\n"); return 1;
    }
    if (!is_zero(bent(-0.5) - ((sqrt(1.25) - 1.0) / 2.0 - 0.5))) {
        printf("Test failed at x = -0.5\n"); return 1;
    }
    if (!is_zero(bent(2.0) - ((sqrt(5.0) - 1.0) / 2.0 + 2.0))) {
        printf("Test failed at x = 2.0\n"); return 1;
    }
    if (!is_zero(bent(-2.0) - ((sqrt(5.0) - 1.0) / 2.0 - 2.0))) {
        printf("Test failed at x = -2.0\n"); return 1;
    }
    if (!is_zero(bent(10.0) - ((sqrt(101.0) - 1.0) / 2.0 + 10.0))) {
        printf("Test failed at x = 10.0\n"); return 1;
    }
    if (!is_zero(bent(-10.0) - ((sqrt(101.0) - 1.0) / 2.0 - 10.0))) {
        printf("Test failed at x = -10.0\n"); return 1;
    }
    printf("test_bent passed\n");
    return 0;
}

int test_bent_derivative() {
    if (!is_zero(bent_derivative(0.0) - 1.0)) {
        printf("Test failed at x = 0.0\n"); return 1;
    }
    if (!is_zero(bent_derivative(1.0) - (1.0 / (2.0 * sqrt(2.0)) + 1.0))) {
        printf("Test failed at x = 1.0\n"); return 1;
    }
    if (!is_zero(bent_derivative(-1.0) - (-1.0 / (2.0 * sqrt(2.0)) + 1.0))) {
        printf("Test failed at x = -1.0\n"); return 1;
    }
    if (!is_zero(bent_derivative(0.5) - (0.5 / (2.0 * sqrt(1.25)) + 1.0))) {
        printf("Test failed at x = 0.5\n"); return 1;
    }
    if (!is_zero(bent_derivative(-0.5) - (-0.5 / (2.0 * sqrt(1.25)) + 1.0))) {
        printf("Test failed at x = -0.5\n"); return 1;
    }
    if (!is_zero(bent_derivative(2.0) - (2.0 / (2.0 * sqrt(5.0)) + 1.0))) {
        printf("Test failed at x = 2.0\n"); return 1;
    }
    if (!is_zero(bent_derivative(-2.0) - (-2.0 / (2.0 * sqrt(5.0)) + 1.0))) {
        printf("Test failed at x = -2.0\n"); return 1;
    }
    if (!is_zero(bent_derivative(10.0) - (10.0 / (2.0 * sqrt(101.0)) + 1.0))) {
        printf("Test failed at x = 10.0\n"); return 1;
    }
    if (!is_zero(bent_derivative(-10.0) - (-10.0 / (2.0 * sqrt(101.0)) + 1.0))) {
        printf("Test failed at x = -10.0\n"); return 1;
    }
    printf("test_bent_derivative passed\n");
    return 0;
}

// ГОЛОВНА ФУНКЦІЯ 

int main() {
    int failed = 0;
    
    if (test_softPlus() != 0) failed = 1;
    if (test_softPlus_derivative() != 0) failed = 1;
    
    if (test_arctan() != 0) failed = 1;
    if (test_arctan_derivative() != 0) failed = 1;
    
    if (test_sigmweight() != 0) failed = 1;
    if (test_sigmweight_derivative() != 0) failed = 1;
    
    if (test_soft_sign() != 0) failed = 1;
    if (derivative_test_soft_sign() != 0) failed = 1;
    
    if (tests() != 0) failed = 1; 
    
    if (test_bent() != 0) failed = 1;
    if (test_bent_derivative() != 0) failed = 1;

    if (failed == 0) {
        printf("All tests passed successfully!\n");
    } else {
        printf("Some tests failed. Check the output above.\n");
    }
    
    return 0;
}

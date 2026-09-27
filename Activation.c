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

bool is_zero(double x){
    return fabs(x) < 1e-9;
}

double arctan(double x){

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



int test_arctan(){

    if(!is_zero(arctan(0.0))){
        printf("Test failed: arctan(0.0) should be 0.0\n");
        return 1;
    }
    if(!is_zero(arctan(1.0) - M_PI/4)){
        printf("Test failed: arctan(1.0) should be approximately π/4\n");
        return 1;
    }
    
    if(!is_zero(arctan(1.0) - M_PI/4)){
        printf("Test failed: arctan(1.0) should be approximately π/4\n");



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
    if (test_softPlus() == 0 && test_softPlus_derivative() == 0) {
    // Запускаємо обидва тести
    if (test_sigmweight() == 0 && test_sigmweight_derivative() == 0) {
        printf("All tests passed successfully!\n");
    } else {
        printf("Some tests failed. Check the output above.\n");
    }
    
    return 0;
}


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

int test_arctan_derivative(){
    if(!is_zero(arctan_derivative(0.0) - 1.0)){
        printf("Test failed: arctan_derivative(0.0) should be 1.0\n");
        return 1;
    }
    if(!is_zero(arctan_derivative(1.0) - 0.5)){
        printf("Test failed: arctan_derivative(1.0) should be approximately 0.5\n");
        return 1;
    }
    if(!is_zero(arctan_derivative(-1.0) - 0.5)){
        printf("Test failed: arctan_derivative(-1.0) should be approximately 0.5\n");
int derivative_test_soft_sign() {
    if (!is_zero(soft_sign_derivative(-1))) {
        printf("test for soft_sign has failed\n");
        return 1;
    }
    if (!is_zero(soft_sign_derivative(0)-1)) {
        printf("test for soft_sign has failed\n");
        return 1;
    }
    if (!is_zero(soft_sign_derivative(1)-0.5)) {
        printf("test for soft_sign has failed\n");
        return 1;
    }
    return 0;
}

double invsqrt(double x, double alpha) {
    return x / sqrt(1.0 + alpha * x * x);
}

double invsqrt_derivative(double x, double alpha) {
    double base = 1.0 + alpha * x * x;
    return 1.0 / (base * sqrt(base));
}

///Tests
int tests() {
    printf("tests ...\n");
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
    }
    if (!isnan(invsqrt_derivative(1.0, -3.0))) {}
    printf("tests are successful\n");
    return 0;
}

#include <stdio.h>
#include <math.h>

double gauss(double x) {
    double res = exp(-x * x);
    return res;
}
double gauss_derivative(double x) {
    double temp = exp(-x * x);
    double derivative = -2.0 * x * temp;
    return derivative;
}

int tests() {
    printf("tests\n");
    printf("gauss(%lf) = %lf (expected 0.367879)\n", 1.0, gauss(1.0));
    printf("gauss_derivative(%lf) = %lf (expected -0.735759)\n", 1.0, gauss_derivative(1.0));
    printf("gauss(%lf) = %lf (expected 1.000000)\n", 0.0, gauss(0.0));
    printf("gauss_derivative(%lf) = %lf (expected 0.000000)\n", 0.0, gauss_derivative(0.0));
    printf("gauss(%lf) = %lf (expected 0.018316)\n", 2.0, gauss(2.0));
    printf("gauss_derivative(%lf) = %lf (expected -0.073263)\n", 2.0, gauss_derivative(2.0));
    return 0;
}

int main() {
    double x;
    tests();
    printf("input x: ");
    scanf("%lf", &x);
    
    double i = gauss(x);
    double j = gauss_derivative(x);
    
    printf("gauss(%lf) = %lf\n", x, i);
    printf("gauss_derivative(%lf) = %lf\n", x, j);
    
    return 0;
}
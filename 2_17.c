#include <stdio.h>
#include <math.h>

double invsqrt(double x, double alpha){
    if (1+alpha*x*x<=0.0) {
        printf("the square root is negative!\n");
        return NAN;
    }
    return x/sqrt(1+alpha*x*x);
}

double invsqrt_derivative(double x, double alpha) {
    if (1+alpha*x*x<=0.0) {
        printf("the square root is negative!\n");
        return NAN;
    }
    double y = pow(1+alpha*x*x, 3);
    return 1/sqrt(y);
}

int tests() {
    printf("tests\n");
    printf("invsqrt(%lf, %lf) = %lf (expected 0.442326)\n", 3.0, 5.0, invsqrt(3.0, 5.0));
    printf("invsqrt_derivative(%lf, %lf) = %lf (expected 0.003205)\n", 3.0, 5.0, invsqrt_derivative(3.0, 5.0));
    printf("invsqrt(%lf, %lf) = %lf (expected: nan)\n", 1.0, -1.0, invsqrt(1.0, -1.0));
    printf("invsqrt_derivative(%lf, %lf) = %lf (expected: nan)\n", 1.0, -1.0, invsqrt_derivative(1.0, -1.0));
    printf("invsqrt(%lf, %lf) = %lf (expected: -0.485495)\n", -2.56, 4.09, invsqrt(-2.56, 4.09));
    printf("invsqrt_derivative(%lf, %lf) = %lf (expected: 0.006821)\n", -2.56, 4.09, invsqrt_derivative(-2.56, 4.09));

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

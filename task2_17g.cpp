# include <stdio.h>
# include <math.h>
#include <ostream>

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

double arctanDerivative(double x) {
    return 1.0 / (1.0 + x * x);
}

int test(){
    printf("%f\n", arctan(0.0));
    printf("%f\n", arctan(1.0));
    printf("%f\n", arctan(-1.0));
    printf("%f\n", arctan(0.5));

    printf("%f\n", arctanDerivative(0.0));
    printf("%f\n", arctanDerivative(1.0));
    printf("%f\n", arctanDerivative(-1.0));
    printf("%f\n", arctanDerivative(0.5));
    return 0;
}

int main() {
    test();
    return 0;
}
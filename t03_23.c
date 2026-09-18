#include <stdio.h>
#include <math.h>
#include <float.h>

double soft_exponential(double a, double x) {
    if (a < 0.0) {
        return -log(1.0 - a * (x + a)) / a;
    } else if (a == 0.0) {
        return x;
    } else {
        return (exp(a * x) - 1.0) / a + a;
    }
}

double soft_exponential_deriv(double a, double x) {
    if (a < 0.0) {
        double denom = 1.0 - a * (x + a);
        if (denom <= 0.0) return DBL_MAX; 
        return 1.0 / denom;
    } else if (a == 0.0) {
        return 1.0;
    } else {
        return exp(a * x);
    }
}

int main() {
    double x = 1.5;
    double a = 0.5;

    printf("%f\n", soft_exponential(-a, x));
    printf("%f\n", soft_exponential_deriv(-a, x));
    
    printf("%f\n", soft_exponential(0, x));
    printf("%f\n", soft_exponential_deriv(0, x));
    
    printf("%f\n", soft_exponential(a, x));
    printf("%f\n", soft_exponential_deriv(a, x));

    return 0;
}

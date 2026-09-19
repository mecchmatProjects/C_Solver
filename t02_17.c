#include <stdio.h>
#include <math.h>

double softSign(double x) {
    return x / (1.0 + fabs(x));
}

double softSign_derivative(double x) {
    double d = 1.0 + fabs(x);
    return 1.0 / (d * d);
}

int main() {
    printf("Test f(0) = %g, df(0) = %g\n", f(0), df(0));
    printf("Test f(1) = %g, df(1) = %g\n", f(1), df(1));

    double x;
    printf("\nEnter x: ");
    scanf("%lf", &x);

    printf("f(%g) = %g\n", x, f(x));
    printf("df(%g) = %g\n", x, df(x));

    return 0;
}

#include <math.h>
#include <stdio.h>
double soft_sign(double x) {
    return x/(1+fabs(x));
}
double derivative(double x) {
    const double h = 1e-5;
    return (soft_sign(x+h)-soft_sign(x-h))/(2*h);
}
int test() {
    printf("soft sign: %lf (expected 0.5)\n", soft_sign(1));
    printf("soft sign: %lf (expected -0.5)\n", soft_sign(-1));
    printf("derivative soft sign: %lf (expected 0.25)\n", derivative(1));
    printf("derivative soft sign: %lf (expected 0.25)\n", derivative(-1));
}
int main() {
    test();
    double x;
    printf("Enter the value of x: ");
    scanf("%lf", &x);
    printf("the soft sign function is %lf\n", soft_sign(x));
    printf("the derivative function is %lf\n", derivative(x));
}
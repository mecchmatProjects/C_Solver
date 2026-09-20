#include <stdio.h>
#include <math.h>
// Функція eReLu
double eReLu(double a, double x)
{
    if (x < 0)
        return a * (exp(x) - 1);
    else
        return 0;
}
// Похідна eReLu
double eReLuDerivative(double a, double x)
{
    if (x < 0)
        return a * exp(x);
    else if (x > 0)
        return 0;
    else
        return NAN; // похідна в x = 0 не існує (якщо a != 0)
}
int main()
{
    double a, x;
    printf("Enter a: ");
    scanf("%lf", &a);
    printf("Enter x: ");
    scanf("%lf", &x);
    printf("eReLu(a, x) = %lf\n", eReLu(a, x));
    double derivative = eReLuDerivative(a, x);
    if (isnan(derivative))
        printf("Derivative does not exist at x = 0\n");
    else
        printf("Derivative = %lf\n", derivative);

    return 0;
}
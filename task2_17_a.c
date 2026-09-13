//
// Created by Олександра on 12.09.2026.
//
#include <stdio.h>
#include <math.h>


double th(double x)
{
    return (exp(x) - exp(-x)) / (exp(x) + exp(-x));
}


double th_der(double x)
{
    return 4.0 / pow(exp(x) + exp(-x), 2);
}

int main()
{
    double x;

    printf("Enter x: ");
    scanf("%lf", &x);

    printf("f(x) = %.6f\n", th(x));
    printf("f'(x) = %.6f\n", th_der(x));

    return 0;
}
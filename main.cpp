#include <stdio.h> #include <math.h>
double bent(double x) { return (sqrt(x * x + 1.0) - 1.0) / 2.0 + x; }
double bent_derivative(double x) { return x / (2.0 * sqrt(x * x + 1.0)) + 1.0; }
double numerical_derivative(double x, double h) { return (bent(x + h) - bent(x - h)) / (2.0 * h); }
int main() { double test_cases[] = {-100.0, -10.0, -1.0, -0.5, 0.0, 0.5, 1.0, 2.0, 10.0, 100.0}; int num_tests = sizeof(test_cases) / sizeof(test_cases[0]); double h = 1e-5;
printf("%-10s | %-15s | %-15s | %-15s | %-10s\n", "x", "bent(x)", "Analytical f'(x)", "Numerical f'(x)", "Diff");
printf("-----------------------------------------------------------------------------------\n");

for (int i = 0; i < num_tests; i++) {
    double x = test_cases[i];
    double f_x = bent(x);
    double df_analytical = bent_derivative(x);
    double df_numerical = numerical_derivative(x, h);
    double diff = fabs(df_analytical - df_numerical);

    printf("%-10.2f | %-15.6f | %-15.6f | %-15.6f | %-10.2e\n", 
           x, f_x, df_analytical, df_numerical, diff);
}

return 0;
}
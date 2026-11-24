
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef double (*ScalarFunction)(double);

static double square(double x) {
    return x * x;
}

static int valid_arguments(ScalarFunction f, double x, double h) {
    return f != NULL && isfinite(x) && isfinite(h) && h > 0.0;
}

// Forward difference
static double derivative_forward(ScalarFunction f, double x, double h) {
    if (!valid_arguments(f, x, h) || !isfinite(x + h))
        return NAN;

    double left = f(x);
    double right = f(x + h);

    if (!isfinite(left) || !isfinite(right))
        return NAN;

    double result = (right - left) / h;
    return isfinite(result) ? result : NAN;
}

// Backward difference
static double derivative_backward(ScalarFunction f, double x, double h) {
    if (!valid_arguments(f, x, h) || !isfinite(x - h))
        return NAN;

    double left = f(x - h);
    double right = f(x);

    if (!isfinite(left) || !isfinite(right))
        return NAN;

    double result = (right - left) / h;
    return isfinite(result) ? result : NAN;
}

// Central difference
static double derivative_central(ScalarFunction f, double x, double h) {
    if (!valid_arguments(f, x, h) || !isfinite(x + h) ||
        !isfinite(x - h) || !isfinite(2.0 * h))
        return NAN;

    double left = f(x - h);
    double right = f(x + h);

    if (!isfinite(left) || !isfinite(right))
        return NAN;

    double result = (right - left) / (2.0 * h);
    return isfinite(result) ? result : NAN;
}

// Таблиця похибок
static int print_derivative_table(FILE *out) {
    if (out == NULL)
        return EXIT_FAILURE;

    const struct {
        const char *name;
        ScalarFunction function;
        double x;
        double exact;
    } examples[] = {
        {"x^2", square, 2.0, 4.0},
        {"sin(x)", sin, 0.0, 1.0},
        {"exp(x)", exp, 0.0, 1.0}
    };

    const struct {
        const char *name;
        double (*calculate)(ScalarFunction, double, double);
    } methods[] = {
        {"forward", derivative_forward},
        {"backward", derivative_backward},
        {"central", derivative_central}
    };

    if (fprintf(out, "%-9s %8s %10s %-9s %10s %17s %17s\n",
                "Function", "x", "Exact", "Method", "h",
                "Approximation", "Absolute error") < 0)
        return EXIT_FAILURE;

    for (size_t i = 0;
         i < sizeof(examples) / sizeof(examples[0]); ++i) {

        for (int k = 1; k <= 8; ++k) {
            double h = pow(10.0, -k);

            for (size_t j = 0;
                 j < sizeof(methods) / sizeof(methods[0]); ++j) {

                double approx = methods[j].calculate(
                    examples[i].function,
                    examples[i].x,
                    h
                );

                double error = fabs(approx - examples[i].exact);

                if (fprintf(out,
                            "%-9s %8.2f %10.6f %-9s %10.1e %17.10f %17.8e\n",
                            examples[i].name,
                            examples[i].x,
                            examples[i].exact,
                            methods[j].name,
                            h,
                            approx,
                            error) < 0)
                    return EXIT_FAILURE;
            }
        }
    }

    return EXIT_SUCCESS;
}

int run_derivative_experiment(void) {
    return print_derivative_table(stdout);
}

#ifndef MINIAI_A6_TEST_BUILD
int main(void) {
    return run_derivative_experiment();
}
#endif

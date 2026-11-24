#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef double (*demo_scalar_fn)(double x);

static int is_valid_step(double h) {
    return isfinite(h) && h > 0.0;
}

static double demo_derivative_forward(demo_scalar_fn f, double x, double h) {
    if (f == NULL || !isfinite(x) || !is_valid_step(h)) {
        return NAN;
    }
    double xp = x + h;
    if (!isfinite(xp)) {
        return NAN;
    }
    double fx = f(x);
    double fxp = f(xp);
    if (!isfinite(fx) || !isfinite(fxp)) {
        return NAN;
    }
    return (fxp - fx) / h;
}

static double demo_derivative_backward(demo_scalar_fn f, double x, double h) {
    if (f == NULL || !isfinite(x) || !is_valid_step(h)) {
        return NAN;
    }
    double xm = x - h;
    if (!isfinite(xm)) {
        return NAN;
    }
    double fx = f(x);
    double fxm = f(xm);
    if (!isfinite(fx) || !isfinite(fxm)) {
        return NAN;
    }
    return (fx - fxm) / h;
}

static double demo_derivative_central(demo_scalar_fn f, double x, double h) {
    if (f == NULL || !isfinite(x) || !is_valid_step(h)) {
        return NAN;
    }
    double xp = x + h;
    double xm = x - h;
    if (!isfinite(xp) || !isfinite(xm)) {
        return NAN;
    }
    double fxp = f(xp);
    double fxm = f(xm);
    if (!isfinite(fxp) || !isfinite(fxm)) {
        return NAN;
    }
    return (fxp - fxm) / (2.0 * h);
}

static double fn_square(double x) { return x * x; }
static double fn_sin(double x) { return sin(x); }
static double fn_exp(double x) { return exp(x); }

static void print_table_for_function(const char* name, demo_scalar_fn f,
    double x, double exact) {
    const double steps[] = { 1e-1, 1e-2, 1e-3, 1e-4, 1e-6, 1e-8 };
    const size_t n_steps = sizeof(steps) / sizeof(steps[0]);

    printf("\n=== Function: %s at x = %.4f (exact f'(x) = %.10f) ===\n",
        name, x, exact);
    printf("%-10s | %-10s | %-16s | %-14s\n",
        "Method", "h", "Approximation", "Abs Error");
    printf("---------------------------------------------------------------\n");

    for (size_t i = 0; i < n_steps; ++i) {
        double h = steps[i];
        double fwd = demo_derivative_forward(f, x, h);
        double bwd = demo_derivative_backward(f, x, h);
        double cen = demo_derivative_central(f, x, h);

        printf("%-10s | %-10.1e | %-16.10f | %-14.6e\n",
            "forward", h, fwd, fabs(fwd - exact));
        printf("%-10s | %-10.1e | %-16.10f | %-14.6e\n",
            "backward", h, bwd, fabs(bwd - exact));
        printf("%-10s | %-10.1e | %-16.10f | %-14.6e\n",
            "central", h, cen, fabs(cen - exact));
    }
}

int run_derivative_demo(void) {
    printf("MiniAI Lab 4 (A10): Numerical Differentiation Demo\n");
    print_table_for_function("f(x) = x^2", fn_square, 2.0, 4.0);
    print_table_for_function("f(x) = sin(x)", fn_sin, 0.0, 1.0);
    print_table_for_function("f(x) = exp(x)", fn_exp, 0.0, 1.0);
    return 0;
}

#ifndef MINIAI_DERIVATIVE_DEMO_NO_MAIN
static int parse_double(const char* str, double* out) {
    if (str == NULL || *str == '\0' || out == NULL) {
        return 0;
    }
    char* end = NULL;
    double val = strtod(str, &end);
    if (end == str || *end != '\0' || !isfinite(val)) {
        return 0;
    }
    *out = val;
    return 1;
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        return run_derivative_demo();
    }

    if (argc != 3) {
        fprintf(stderr, "Usage: %s [<x> <h>]\n", argv[0]);
        return 1;
    }

    double x = 0.0;
    double h = 0.0;
    if (!parse_double(argv[1], &x) || !parse_double(argv[2], &h) || !is_valid_step(h)) {
        fprintf(stderr, "Error: invalid arguments. Expected finite x and h > 0.\n");
        return 1;
    }

    double exact = 2.0 * x;
    double fwd = demo_derivative_forward(fn_square, x, h);
    double bwd = demo_derivative_backward(fn_square, x, h);
    double cen = demo_derivative_central(fn_square, x, h);

    if (!isfinite(fwd) || !isfinite(bwd) || !isfinite(cen)) {
        fprintf(stderr, "Error: numerical differentiation failed (non-finite result).\n");
        return 1;
    }

    printf("Custom evaluation for f(x) = x^2 at x = %.6f, h = %.2e (exact = %.10f)\n",
        x, h, exact);
    printf("forward : %.10f (abs error = %.6e)\n", fwd, fabs(fwd - exact));
    printf("backward: %.10f (abs error = %.6e)\n", bwd, fabs(bwd - exact));
    printf("central : %.10f (abs error = %.6e)\n", cen, fabs(cen - exact));
    return 0;
}
#endif
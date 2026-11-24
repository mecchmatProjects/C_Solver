#include "test_functions.h"

#include <math.h>

double test_poly_x2(double x) { return x * x; }
double test_poly_x2_deriv(double x) { return 2.0 * x; }

double test_sin(double x) { return sin(x); }
double test_sin_deriv(double x) { return cos(x); }

double test_exp(double x) { return exp(x); }
double test_exp_deriv(double x) { return exp(x); }

double test_poly_x3(double x) { return x * x * x; }
double test_poly_x3_deriv(double x) { return 3.0 * x * x; }
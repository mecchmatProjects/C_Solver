#include <iostream>
#include <cmath>
using namespace std;

bool is_zero(double x) {
    return fabs(x) < 1e-9;
}
double gauss(double x) {
    return exp(-x * x);
}

double gauss_derivative(double x) {
    return -2 * x * exp(-x * x);
}

int test_gauss() {
    if (!is_zero(gauss(0.0) - 1.0)) {
        cout << "Test failed: gauss(0.0) should be 1.0" << endl;
        return 1;
    }
    if (!is_zero(gauss(1.0) - exp(-1.0))) {
        cout << "Test failed: gauss(1.0) should be approximately e^(-1)" << endl;
        return 1;
    }

    return 0;
}
int test_gauss_derivative() {
    if (!is_zero(gauss_derivative(0.0))) {
        cout << "Test failed: gauss_derivative(0.0) should be 0.0" << endl;
        return 1;
    }
    if (!is_zero(gauss_derivative(1.0) - (-2.0 * exp(-1.0)))) {
        cout << "Test failed: gauss_derivative(1.0) should be approximately -2*e^(-1)" << endl;
        return 1;
    }
    return 0;
}

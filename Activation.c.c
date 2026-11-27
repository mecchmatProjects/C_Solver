#include <iostream>
#include <cmath>

bool is_zero(double value, double eps = 1e-6) {
    return std::abs(value) < eps;
}

double bent(double x) {
    return (std::sqrt(x * x + 1.0) - 1.0) / 2.0 + x;
}

double bent_derivative(double x) {
    return x / (2.0 * std::sqrt(x * x + 1.0)) + 1.0;
}

int test_bent() {
    if (!is_zero(bent(0.0))) {
        std::cout << "Test failed at x = 0.0\n";
        return 1;
    }
    if (!is_zero(bent(1.0) - ((std::sqrt(2.0) - 1.0) / 2.0 + 1.0))) {
        std::cout << "Test failed at x = 1.0\n";
        return 1;
    }
    if (!is_zero(bent(-1.0) - ((std::sqrt(2.0) - 1.0) / 2.0 - 1.0))) {
        std::cout << "Test failed at x = -1.0\n";
        return 1;
    }
    if (!is_zero(bent(0.5) - ((std::sqrt(1.25) - 1.0) / 2.0 + 0.5))) {
        std::cout << "Test failed at x = 0.5\n";
        return 1;
    }
    if (!is_zero(bent(-0.5) - ((std::sqrt(1.25) - 1.0) / 2.0 - 0.5))) {
        std::cout << "Test failed at x = -0.5\n";
        return 1;
    }
    if (!is_zero(bent(2.0) - ((std::sqrt(5.0) - 1.0) / 2.0 + 2.0))) {
        std::cout << "Test failed at x = 2.0\n";
        return 1;
    }
    if (!is_zero(bent(-2.0) - ((std::sqrt(5.0) - 1.0) / 2.0 - 2.0))) {
        std::cout << "Test failed at x = -2.0\n";
        return 1;
    }
    if (!is_zero(bent(10.0) - ((std::sqrt(101.0) - 1.0) / 2.0 + 10.0))) {
        std::cout << "Test failed at x = 10.0\n";
        return 1;
    }
    if (!is_zero(bent(-10.0) - ((std::sqrt(101.0) - 1.0) / 2.0 - 10.0))) {
        std::cout << "Test failed at x = -10.0\n";
        return 1;
    }

    std::cout << "test_bent passed\n";
    return 0;
}

int test_bent_derivative() {
    if (!is_zero(bent_derivative(0.0) - 1.0)) {
        std::cout << "Test failed at x = 0.0\n";
        return 1;
    }
    if (!is_zero(bent_derivative(1.0) - (1.0 / (2.0 * std::sqrt(2.0)) + 1.0))) {
        std::cout << "Test failed at x = 1.0\n";
        return 1;
    }
    if (!is_zero(bent_derivative(-1.0) - (-1.0 / (2.0 * std::sqrt(2.0)) + 1.0))) {
        std::cout << "Test failed at x = -1.0\n";
        return 1;
    }
    if (!is_zero(bent_derivative(0.5) - (0.5 / (2.0 * std::sqrt(1.25)) + 1.0))) {
        std::cout << "Test failed at x = 0.5\n";
        return 1;
    }
    if (!is_zero(bent_derivative(-0.5) - (-0.5 / (2.0 * std::sqrt(1.25)) + 1.0))) {
        std::cout << "Test failed at x = -0.5\n";
        return 1;
    }
    if (!is_zero(bent_derivative(2.0) - (2.0 / (2.0 * std::sqrt(5.0)) + 1.0))) {
        std::cout << "Test failed at x = 2.0\n";
        return 1;
    }
    if (!is_zero(bent_derivative(-2.0) - (-2.0 / (2.0 * std::sqrt(5.0)) + 1.0))) {
        std::cout << "Test failed at x = -2.0\n";
        return 1;
    }
    if (!is_zero(bent_derivative(10.0) - (10.0 / (2.0 * std::sqrt(101.0)) + 1.0))) {
        std::cout << "Test failed at x = 10.0\n";
        return 1;
    }
    if (!is_zero(bent_derivative(-10.0) - (-10.0 / (2.0 * std::sqrt(101.0)) + 1.0))) {
        std::cout << "Test failed at x = -10.0\n";
        return 1;
    }

    std::cout << "test_bent_derivative passed\n";
    return 0;
}

int main() {
    int res1 = test_bent();
    int res2 = test_bent_derivative();

    if (res1 == 0 && res2 == 0) {
        std::cout << "All tests passed\n";
    }

    return 0;
}
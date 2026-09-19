double leakyRelu(double x, double a) {
    if (x < 0) {
        return a * x;
    }
    else {
        return 0.0;
    }
}
double leakyReluDerivative(double x, double a) {
    if (x < 0) {
        return a;
    }
    else {
        return 0.0;
    }
}

int main() {
    double x = -2.0;
    double a = 0.1;
    std::cout << "leakyRelu: " << leakyRelu(x, a) << std::endl;
    std::cout << "Derivative: " << leakyReluDerivative(x, a) << std::endl;
    return 0;
}
#include <stdio.h>
#include <math.h>

double gauss(double x) {
    double y = exp(-x * x);
    return y;


}

double gauss_devariative(double x) {
    double y = gauss(x);
    double z = -2 * x * y;
    return z;

}

int main() {
    double x = 0.5;
    double result_f = gauss(x);
    double result_fd = gauss_devariative(x);
    //Tests//
    //f(0.5) = e^(-0.25) = 0.7788078
    //f'(0.5) = -2 * 0.5 * e^(-0.25) = -1 * e^(-0.25) = -0.7788078
    double expected_f = 0.7788007830714049;
    double expected_fd = -0.7788007830714049;
    double epsilon = 1e-7;
    printf("Testing for x = %.2f:\n", x);
    printf("f(x) = %.2f\n", result_f, expected_f);
    printf("f'(x) = %.2f\n", result_fd, expected_fd);

    if (fabs(result_f - expected_f) < epsilon && fabs(result_fd - expected_fd) < epsilon) {
        printf("Test PASSED\n");
    } else {
        printf("Test FAILED\n");
    }


    return 0;
}



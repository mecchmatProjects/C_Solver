#include <stdio.h>
#include <math.h>
#include <stdbool.h>

static is_zero(double x) {
    return fabs(x) < 1e-9;
}

// --- Пункт ж) sinc ---

double sinc(double x) {  //Функція sinc
    if (is_zero(x)) {
        return 1.0;
    } else {
        return sin(x) / x;
    }
}

double sinc_derivative(double x) {  //Похідна функції sinc
    if (is_zero(x)) {
        return 0.0;
    } else {
        return (x * cos(x) - sin(x)) / (x * x);
    }
}

int test_sinc(void) { //Тест для функції sinc
    if (!is_zero(sinc(0) - 1.0)) {
        printf("Test sinc for 0 is failed\n");
        return 1;
    }
    if (!is_zero(sinc(1.0) - sin(1.0))) {
        printf("Test sinc for 1 is failed\n");
        return 1;
    }
    return 0;
}

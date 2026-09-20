//
// Created by Katya on 13.09.2026.
//
#include <stdio.h>

int test_onestep(void);
int test_sinc(void);
int test_soft_exponential(void);
int test_Relu(void);
int test_sRelu(void);

int main() {
    // катя
    if (test_onestep() == 0) {
        printf("Everything is okay!\n");
    } else {
        printf("Test failed!\n");
    }
    // Хорошун Маша
    if (test_sinc() == 0) { // <-- 2. Викликаємо перевірку sinc
        printf("sinc test passed!\n");
    } else {
        printf("sinc test failed!\n");
    }
    // Віра
    if (test_soft_exponential() == 0) {
        printf("soft_exponential test passed!\n");
    } else {
        printf("soft_exponential test failed!\n");
    }
    // Артем
    if (test_Relu() == 0) {
        printf("ReLU test passed!\n");
    } else {
        printf("ReLU test failed!\n");
    }
    // Марія Лемента
    if (test_sRelu() == 0) {
        printf("sRelu test passed!\n");
    } else {
        printf("sRelu test failed!\n");
    }
    return 0;
}
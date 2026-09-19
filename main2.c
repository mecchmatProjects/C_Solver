//
// Created by Katya on 13.09.2026.
//
#include <stdio.h>

int test_onestep(void);
int test_sinc(void);

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

    return 0;
}
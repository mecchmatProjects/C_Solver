//
// Created by Katya on 06.11.2026.
//
#include <stdio.h>

#include "miniai/math/vector.h"

int main(void) {
    const double a[] = {1.0, 2.0};
    const double b[] = {3.0, 4.0};
    double out[2];

    if (miniai_vector_add(a, b, out, 2) != 0) {
        fputs("Vector addition failed\n", stderr);
        return 1;
    }

    printf("[1, 2] + [3, 4] = [%g, %g]\n", out[0], out[1]);
    return 0;
}
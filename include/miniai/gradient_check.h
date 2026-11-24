#ifndef MINIAI_GRADIENT_CHECK_H
#define MINIAI_GRADIENT_CHECK_H

#include <stddef.h>
#include <stdio.h>

/*
    Prints a coordinate-wise comparison report for exact and approximate 
    gradients.

    stream - output stram (must not be NULL).
    exact - exact (analitical) gradient array of size n.
    approx - approximate (numerical) gradient array of size n.
    n - number of elements (must be > 0).
    abs_tol - non-negative finite absolute tolerance.
    rel_tol - non-negative finite relative tolerance.
    return 0 if all pass, 1 on mismatch, -1 on invalid arguments.
*/

int miniai_gradient_check_report(FILE *stream, const double exact[],
const double approa[], size_t n, double abs_tol, double rel_tol);

#endif /* MINIAI_GRADIENT_CHECK_H */
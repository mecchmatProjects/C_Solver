#ifndef MINIAI_GRADIENT_H
#define MINIAI_GRADIENT_H

#include <stddef.h>

typedef double (*miniai_objective_function)(const double x[], size_t n,
                                            void *context);

enum {
    MINIAI_GRADIENT_OK = 0,
    MINIAI_GRADIENT_INVALID_ARGUMENT = 1,
    MINIAI_GRADIENT_NONFINITE_OBJECTIVE = 2,
    MINIAI_GRADIENT_NO_MEMORY = 3
};

#endif
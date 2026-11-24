#ifndef MINIAI_OBJECTIVE_H
#define MINIAI_OBJECTIVE_H

#include <stddef.h>

typedef double (*miniai_objective_function)(const double x[], size_t n, void *context);

#endif
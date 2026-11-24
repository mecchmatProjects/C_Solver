#ifndef MINIAI_OBJECTIVE_H
#define MINIAI_OBJECTIVE_H 

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef double (*miniai_objective_function)(const double x[], size_t n, void *context);

#ifdef __cplusplus
}
#endif

#endif

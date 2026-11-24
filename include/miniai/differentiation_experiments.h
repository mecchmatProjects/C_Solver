#ifndef MINIAI_DIFFERENTIATION_EXPERIMENTS_H
#define MINIAI_DIFFERENTIATION_EXPERIMENTS_H

#include "miniai/differentiation.h"

int miniai_step_sweep(miniai_scalar_function f, double exact, double x,
    const double steps[], size_t n,
    double errors[], size_t* best_index);

#endif
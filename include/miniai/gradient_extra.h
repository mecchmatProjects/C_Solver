#ifndef MINIAI_GRADIENT_EXTRA_H
#define MINIAI_GRADIENT_EXTRA_H

#include "miniai/gradient.h"

int miniai_gradient_central_steps(miniai_objective_function f,
                                  const double x[],
                                  const double steps[],
                                  size_t n,
                                  void *context,
                                  double gradient[]);

#endif
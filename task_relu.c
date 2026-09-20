#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <float.h>

double ReLu(double x)
{
 if (x < 0)
  return 0;
 else
  return x;
}
double ReLu_derivative(double x)
{
 if (x > 0)
  return 1.0;
 else if (x < 0)
  return 0.0;
 else
  return DBL_MAX;
}

int test_Relu(void)
{
 if (fabs(ReLu(-2.0) - 0.0) >= 1e-9)
  return 1;

 if (fabs(ReLu(0.0) - 0.0) >= 1e-9)
  return 1;

 if (fabs(ReLu(2.0) - 2.0) >= 1e-9)
  return 1;

 if (fabs(ReLu_derivative(-2.0) - 0.0) >= 1e-9)
  return 1;

 if (fabs(ReLu_derivative(2.0) - 1.0) >= 1e-9)
  return 1;

 if (ReLu_derivative(0.0) != DBL_MAX)
  return 1;

 return 0;
}
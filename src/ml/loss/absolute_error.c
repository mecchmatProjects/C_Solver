#include <math.h>
#include <stdio.h>

double miniai_absolute_error(double prediction, double target) {
    if (!isfinite(prediction)||!isfinite(target)) {
        return NAN; // check for infinity or NaN in arguments
    }
    return fabs(prediction - target); // signed zero works out automatically
}
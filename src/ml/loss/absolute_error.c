#include <math.h>
#include <stdio.h>

double miniai_absolute_error(double prediction, double target) {
    if (!isfinite(prediction)||!isfinite(target)) {
        return NAN; // check for infinity or NaN in arguments
    }
    return fabs(prediction - target); // signed zero works out automatically
}

double miniai_absolute_error_derivative(double prediction, double target) {
    if (!isfinite(prediction)||!isfinite(target)) {
        return NAN;
    }
    double d = prediction - target;
    if (d > 0.0) {
        return 1;
    }
    else if (d < 0.0) {
        return -1;
    }
    else {
        return 0.0;
    }
}
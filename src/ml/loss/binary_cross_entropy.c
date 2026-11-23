#include "miniai/ml/loss/losses.h"

#include <math.h>

#define MINIAI_BCE_EPS 1e-12

static double miniai_bce_clip_prediction(double prediction)
{
    if (prediction < MINIAI_BCE_EPS) {
        return MINIAI_BCE_EPS;
    }
    if (prediction > 1.0 - MINIAI_BCE_EPS) {
        return 1.0 - MINIAI_BCE_EPS;
    }
    return prediction;
}

double miniai_binary_cross_entropy(double prediction, double target)
{
    double clipped;

    if (!isfinite(prediction) || !isfinite(target) ||
        prediction < 0.0 || prediction > 1.0 ||
        target < 0.0 || target > 1.0) {
        return NAN;
    }

    clipped = miniai_bce_clip_prediction(prediction);
    return -(target * log(clipped) +
             (1.0 - target) * log1p(-clipped));
}

double miniai_binary_cross_entropy_derivative(double prediction,
                                              double target)
{
    double clipped;

    if (!isfinite(prediction) || !isfinite(target) ||
        prediction < 0.0 || prediction > 1.0 ||
        target < 0.0 || target > 1.0) {
        return NAN;
    }

    clipped = miniai_bce_clip_prediction(prediction);
    return -target / clipped + (1.0 - target) / (1.0 - clipped);
}

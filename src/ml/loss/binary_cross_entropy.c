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
# include <math.h>

// Helper function to clip the prediction to [eps, 1-eps]
// Marked as static to avoid conflicts if another student adds their own version later
static double clip_prediction(double p){
    const double eps = 1e-12;
    if(p < eps){
        return eps;
    }
    if(p > 1.0 - eps){
        return 1.0 - eps;
    }
    return p;
}

/*
    Calculate the derivative of the BCE loss.

    Integration requirement note:
    This derivative is with respect to the clipped prediction (p),
    not the exect derivative of the hard-clipping composite at saturation.
*/
double miniai_binary_cross_entropy_derivative(double prediction,double target){
    // Target must be finite and within [0, 1] (supports soft labels)
    if(!isfinite(target) || target < 0.0 || target > 1.0){
        return NAN;
    }

    // Prediction must be finite
    if(!isfinite(prediction)){
        return NAN;
    }

    // Clip prediction to avoid division by zero
    double p_c = clip_prediction(prediction);

    // Calculate derivative: -y/p + (1-y)/(1-p)
    return (-target / p_c) + ((1.0 - target) / (1.0 - p_c));
}

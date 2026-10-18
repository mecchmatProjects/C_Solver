#include "miniai/ml/activation/s_relu.h"

#include <float.h>
#include <math.h>

static double s_relu_value(const Activation *activation, double x) {
    const double tl = activation->s_relu.tl;
    const double tr = activation->s_relu.tr;

    if (x <= tl) {
        return tl + activation->s_relu.al * (x - tl);
    }
    if (x < tr) {
        return 0.0;
    }
    return tr + activation->s_relu.ar * (x - tr);
}

static double s_relu_derivative(const Activation *activation, double x) {
    const double tl = activation->s_relu.tl;
    const double tr = activation->s_relu.tr;

    if (fabs(x - tl) < 1e-9 || fabs(x - tr) < 1e-9) {
        return DBL_MAX;
    }
    if (x < tl) {
        return activation->s_relu.al;
    }
    if (x < tr) {
        return 0.0;
    }
    return activation->s_relu.ar;
}

static const ActivationVTable S_RELU_VTABLE = {
    s_relu_value, s_relu_derivative
};

ActivationStatus activation_s_relu_init(Activation *activation,
                                        double tl, double tr,
                                        double al, double ar) {
    if (activation == NULL || !isfinite(tl) || !isfinite(tr) ||
        !isfinite(al) || !isfinite(ar) || tl >= tr) {
        return ACTIVATION_STATUS_INVALID_ARGUMENT;
    }

    activation->vtable = &S_RELU_VTABLE;
    activation->parameter = 0.0;
    activation->s_relu.tl = tl;
    activation->s_relu.tr = tr;
    activation->s_relu.al = al;
    activation->s_relu.ar = ar;
    return ACTIVATION_STATUS_OK;
}

#include "miniai/ml/activation/s_relu.h"

#include <float.h>
#include <math.h>

static const double TL = -1.0;
static const double TR = 1.0;
static const double AL = 0.2;
static const double AR = 0.3;

static double s_relu_value(const Activation *activation, double x) {
    (void)activation;

    if (x <= TL) {
        return TL + AL * (x - TL);
    }
    if (x < TR) {
        return 0.0;
    }
    return TR + AR * (x - TR);
}

static double s_relu_derivative(const Activation *activation, double x) {
    (void)activation;

    if (fabs(x - TL) < 1e-9 || fabs(x - TR) < 1e-9) {
        return DBL_MAX;
    }
    if (x < TL) {
        return AL;
    }
    if (x < TR) {
        return 0.0;
    }
    return AR;
}

static const ActivationVTable S_RELU_VTABLE = {
    s_relu_value, s_relu_derivative
};

ActivationStatus activation_s_relu_init(Activation *activation) {
    if (activation == NULL) {
        return ACTIVATION_STATUS_INVALID_ARGUMENT;
    }

    activation->vtable = &S_RELU_VTABLE;
    activation->parameter = 0.0;
    return ACTIVATION_STATUS_OK;
}

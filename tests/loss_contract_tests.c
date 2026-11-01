#include "miniai/ml/loss/losses.h"

typedef double (*loss_fn)(double, double);
typedef double (*loss_with_delta_fn)(double, double, double);
typedef double (*vector_loss_fn)(const double[], const double[], size_t);

int main(void)
{
    loss_fn f1 = miniai_squared_error;
    loss_fn f2 = miniai_squared_error_derivative;
    loss_fn f3 = miniai_absolute_error;
    loss_fn f4 = miniai_absolute_error_derivative;
    loss_fn f5 = miniai_binary_cross_entropy;
    loss_fn f6 = miniai_binary_cross_entropy_derivative;
    loss_fn f7 = miniai_log_cosh_loss;
    loss_fn f8 = miniai_log_cosh_loss_derivative;

    loss_with_delta_fn f9 = miniai_huber_loss;
    loss_with_delta_fn f10 = miniai_huber_loss_derivative;

    vector_loss_fn f11 = miniai_mse;
    vector_loss_fn f12 = miniai_mae;

    (void)f1; (void)f2; (void)f3; (void)f4;
    (void)f5; (void)f6; (void)f7; (void)f8;
    (void)f9; (void)f10; (void)f11; (void)f12;

    return 0;
}
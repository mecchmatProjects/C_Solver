#include "miniai/ml/loss/losses.h"
#include "miniai/ml/loss/losses.h"

typedef double (*scalar_loss_fn)(double, double);
typedef double (*huber_loss_fn)(double, double, double);
typedef double (*vector_loss_fn)(const double[], const double[], size_t);

#define HAS_TYPE(fn, type) _Generic(&(fn), type: 1, default: 0)

_Static_assert(HAS_TYPE(miniai_squared_error, scalar_loss_fn), "squared_error");
_Static_assert(HAS_TYPE(miniai_squared_error_derivative, scalar_loss_fn), "squared_error_derivative");
_Static_assert(HAS_TYPE(miniai_absolute_error, scalar_loss_fn), "absolute_error");
_Static_assert(HAS_TYPE(miniai_absolute_error_derivative, scalar_loss_fn), "absolute_error_derivative");
_Static_assert(HAS_TYPE(miniai_binary_cross_entropy, scalar_loss_fn), "binary_cross_entropy");
_Static_assert(HAS_TYPE(miniai_binary_cross_entropy_derivative, scalar_loss_fn), "binary_cross_entropy_derivative");
_Static_assert(HAS_TYPE(miniai_huber_loss, huber_loss_fn), "huber_loss");
_Static_assert(HAS_TYPE(miniai_huber_loss_derivative, huber_loss_fn), "huber_loss_derivative");
_Static_assert(HAS_TYPE(miniai_log_cosh_loss, scalar_loss_fn), "log_cosh_loss");
_Static_assert(HAS_TYPE(miniai_log_cosh_loss_derivative, scalar_loss_fn), "log_cosh_loss_derivative");
_Static_assert(HAS_TYPE(miniai_mse, vector_loss_fn), "mse");
_Static_assert(HAS_TYPE(miniai_mae, vector_loss_fn), "mae");

int main(void) {
    return 0;
}

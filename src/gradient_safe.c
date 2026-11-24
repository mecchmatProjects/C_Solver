
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>

typedef double (*miniai_objective_function)(
const double parameters[],
size_t n
);

static int miniai_gradient_validate_args(miniai_objective_function f,
                                         const double x[], size_t n,
                                         double h, const double gradient[]) {
    if ( f== NULL || gradient==NULL || x==NULL || n==0 ) {
        return -1;
    }

    if ( !isfinite(h) || h <= 0.0 ) {
        return -1;
    }

    if ( n > SIZE_MAX / sizeof(double) ) {
        return -2;
    }
    return 0;
}

int miniai_gradient_forward_safe(miniai_objective_function f, const double x[],
    size_t n, double h, void *context, double gradient[]) {

    int status = miniai_gradient_validate_args(f, x, n, h, gradient);
    if (status != 0) {
        return status;
    }

    size_t bytes = n * sizeof(double);

    double *x_curr = malloc(bytes);
    if ( x_curr == NULL ) {
        return -3;
    }

    double *temp_grad = malloc(bytes);
    if (temp_grad == NULL) {
        free( x_curr );
        return -3;
    }

    for (size_t i = 0; i < n; ++i) {
        x_curr[i] = x[i];
    }


    double f0 = f( x_curr , n, context );
    if (!isfinite(f0)) {
        free( temp_grad );
        free( x_curr );
        return -4;
    }

    for ( size_t i = 0; i < n; i++ ) {
        double orig_xi = x_curr[i]; // беремо точку з масиву
        x_curr[i] = orig_xi + h; // приріст

        double fh = f( x_curr, n, context ); // рахумо f
        x_curr[i] = orig_xi;

        double deriv = (fh - f0) / h; // рахуємо цю похідну
        if ( !isfinite(fh) || !isfinite(deriv) ) {
            free(temp_grad);
            free( x_curr );
            return -4;
        }
        temp_grad[i] = deriv;
    }

    for (size_t i = 0; i < n; ++i) { // переписуємо в масив
        gradient[i] = temp_grad[i];
    }


    free( temp_grad );
    free( x_curr );
    return 0;
}


#include "miniai/gradient_check.h"

#include <stdio.h>

int main(void) {
    // Example: F(x0, x1) = x0^2 + 3*x1^2 at point (1, 2), exact gradient is (2, 12)
    const double exact_ok[] = {2.0, 12.0};
    const double approx_num[] = {2.0000005, 11.9999992};

    printf("Case 1: Correct analytical gradient\n");
    int status_ok = miniai_gradient_check_report(stdout, exact_ok, approx_num, 2, 1e-6, 1e-5);
    printf("Return status: %d (expected 0)\n\n", status_ok);

    // Intentional mistake in coordinate 1 (10.0 instead of 12.0)
    const double exact_buggy[] = {2.0, 10.0};

    printf("Case 2: Buggy analytical gradient\n");
    int status_fail = miniai_gradient_check_report(stdout, exact_buggy, approx_num,
                                                   2, 1e-6, 1e-5);
    printf("Return status: %d (expected 1)\n", status_fail);

        return 0;
}
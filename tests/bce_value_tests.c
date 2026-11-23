#include "miniai/ml/loss/losses.h"

#include <math.h>
#include <stdio.h>

static int failures = 0;
static int checks = 0;

static void expect_near(double actual, double expected,
                        const char *message)
{
    ++checks;
    if (!isfinite(actual) ||
        fabs(actual - expected) >
            1e-12 + 1e-9 * fmax(fabs(actual), fabs(expected))) {
        fprintf(stderr, "FAIL: %s (actual %.17g, expected %.17g)\n",
                message, actual, expected);
        ++failures;
    }
}

static void expect_nan(double actual, const char *message)
{
    ++checks;
    if (!isnan(actual)) {
        fprintf(stderr, "FAIL: %s (actual %.17g, expected NAN)\n",
                message, actual);
        ++failures;
    }
}

int main(void)
{
    const double ln2 = 0.69314718055994530942;

    expect_near(miniai_binary_cross_entropy(0.5, 0.0), ln2,
                "p=0.5, y=0");
    expect_near(miniai_binary_cross_entropy(0.5, 1.0), ln2,
                "p=0.5, y=1");
    expect_near(miniai_binary_cross_entropy(0.5, 0.25),
                ln2, "p=0.5, soft target y=0.25");
    expect_near(miniai_binary_cross_entropy(0.9, 1.0),
                -log(0.9), "correct prediction");
    expect_near(miniai_binary_cross_entropy(0.1, 0.0),
                -log1p(-0.1), "correct negative-class prediction");

    expect_near(miniai_binary_cross_entropy(0.0, 0.0),
                -log1p(-1e-12), "p=0 clipped loss");
    expect_near(miniai_binary_cross_entropy(1.0, 1.0),
                -log1p(-1e-12), "p=1 clipped loss");

    expect_nan(miniai_binary_cross_entropy(-0.1, 0.5),
               "prediction below 0");
    expect_nan(miniai_binary_cross_entropy(1.1, 0.5),
               "prediction above 1");
    expect_nan(miniai_binary_cross_entropy(0.5, -0.1),
               "target below 0");
    expect_nan(miniai_binary_cross_entropy(0.5, 1.1),
               "target above 1");
    expect_nan(miniai_binary_cross_entropy(NAN, 0.5),
               "NaN prediction");
    expect_nan(miniai_binary_cross_entropy(0.5, INFINITY),
               "infinite target");

    expect_near(miniai_binary_cross_entropy_derivative(0.5, 1.0),
                -2.0, "derivative y=1");
    expect_near(miniai_binary_cross_entropy_derivative(0.5, 0.0),
                2.0, "derivative y=0");

    if (failures != 0) {
        fprintf(stderr, "%d of %d checks failed\n", failures, checks);
        return 1;
    }

    printf("%d BCE checks passed\n", checks);
    return 0;
}

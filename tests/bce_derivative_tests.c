#include <math.h>
#include <stdio.h>

// Include the common header for loss functions here insted of using extern if available
extern double miniai_binary_cross_entropy_derivative(double prediction, double target);

static int failures = 0;
static int checks = 0;

static void expect_near(double actual, double expected, const char *message){
    ++checks;
    // Relative tolarence for large numbers, absolute for small numbers
    double tolerance = 1e-7 * fmax(1.0, fabs(expected));
    if(!(fabs(actual - expected) <= tolerance)){
        fprintf(stderr, "FAIL: %s (actual %.17g, expected %.17g)\n", message, actual, expected);
        ++failures;
    }
}

static void expect_nan(double actual, const char *message){
    ++checks;
    if(!isnan(actual)){
        fprintf(stderr, "FAIL: %s (expected NAN, got %.17g)\n", message, actual);
        ++failures;
    }
}

static void test_bce_derivative(void){
    // 1. Normal values
    expect_near(miniai_binary_cross_entropy_derivative(0.5, 1.0), -2.0, "BCE derivative for p=0.5, y=1.0");
    expect_near(miniai_binary_cross_entropy_derivative(0.5, 0.0), 2.0, "BCE derivative for p=0.5, y=0.0");

    // 2. Edge cases (clipping works at eps = 1e-12)
    // If p=0.0, it is clipped to 1e-12. -1 / 1e-12 = -1e12
    expect_near(miniai_binary_cross_entropy_derivative(0.0, 1.0), -1e12, "BCE derivative with clipping near 0");
    // If p=1.0, it is clipped to 1.0 - 1e-12.
    double expected_edge = 1.0 / (1.0 - (1.0 - 1e-12));
    expect_near(miniai_binary_cross_entropy_derivative(1.0, 0.0), expected_edge, "BCE derivative with clipping near 1");
    // 3. Invalid data (must return NAN)
    expect_nan(miniai_binary_cross_entropy_derivative(0.5, 1.5), "reject target > 1.0");
    expect_nan(miniai_binary_cross_entropy_derivative(0.5, -0.5), "reject target < 0.0");
    expect_nan(miniai_binary_cross_entropy_derivative(NAN, 1.0), "reject NaN prediction");
    expect_nan(miniai_binary_cross_entropy_derivative(0.5, NAN), "reject NaN target");

}

int main(void){
    test_bce_derivative();

    if(failures != 0){
        fprintf(stderr, "%d of %d BCE derivative checks failed\n", failures, checks);
        return 1;
    }

    printf("%d BCE derivative checks passed\n", checks);
    return 0;
}
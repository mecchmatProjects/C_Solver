#include <stdio.h>
#include <math.h>

extern double miniai_huber_loss_derivative(double prediction, double target, double delta);

static int failures = 0;
static int checks = 0;

static void expect_near(double actual, double expected, const char* message) {
    ++checks;
    // Relative tolerance for large numbers, absolute for small numbers
    double tolerance = 1e-7 * fmax(1.0, fabs(expected));
    if (!(fabs(actual - expected) <= tolerance)) {
        fprintf(stderr, "FAIL: %s (actual %.17g, expected %.17g)\n", message, actual, expected);
        ++failures;
    }
}

static void test_huber_derivative(void) {
    // 1. Внутрішня область (|e| <= delta)
    // e = 0.0 (prediction = 1.0, target = 1.0, delta = 1.0) -> очікується 0.0
    expect_near(miniai_huber_loss_derivative(1.0, 1.0, 1.0), 0.0, "Huber derivative for e=0");

    // e = 0.5 (prediction = 1.5, target = 1.0, delta = 1.0) -> очікується 0.5
    expect_near(miniai_huber_loss_derivative(1.5, 1.0, 1.0), 0.5, "Huber derivative for e within delta (positive)");

    // e = -0.5 (prediction = 0.5, target = 1.0, delta = 1.0) -> очікується -0.5
    expect_near(miniai_huber_loss_derivative(0.5, 1.0, 1.0), -0.5, "Huber derivative for e within delta (negative)");

    // 2. Граничні випадки (|e| == delta)
    // e = delta (prediction = 2.0, target = 1.0, delta = 1.0) -> очікується 1.0
    expect_near(miniai_huber_loss_derivative(2.0, 1.0, 1.0), 1.0, "Huber derivative at upper boundary e = delta");

    // e = -delta (prediction = 0.0, target = 1.0, delta = 1.0) -> очікується -1.0
    expect_near(miniai_huber_loss_derivative(0.0, 1.0, 1.0), -1.0, "Huber derivative at lower boundary e = -delta");

    // 3. Зовнішня область (|e| > delta)
    // e = 2.0 (prediction = 3.0, target = 1.0, delta = 1.0) -> очікується delta * 1.0 = 1.0
    expect_near(miniai_huber_loss_derivative(3.0, 1.0, 1.0), 1.0, "Huber derivative for e > delta");

    // e = -2.0 (prediction = -1.0, target = 1.0, delta = 1.0) -> очікується delta * (-1.0) = -1.0
    expect_near(miniai_huber_loss_derivative(-1.0, 1.0, 1.0), -1.0, "Huber derivative for e < -delta");

    // 4. Граничний випадок: delta <= 0 (очікується обробка / повернення 0.0)
    expect_near(miniai_huber_loss_derivative(2.0, 1.0, 0.0), 0.0, "Huber derivative with delta = 0");
    expect_near(miniai_huber_loss_derivative(2.0, 1.0, -1.0), 0.0, "Huber derivative with negative delta");
}

int main(void) {
    test_huber_derivative();

    if (failures > 0) {
        fprintf(stderr, "FAILURE: %d of %d checks failed.\n", failures, checks);
        return 1;
    }

    printf("SUCCESS: All %d checks passed.\n", checks);
    return 0;
}
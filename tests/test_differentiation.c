/* Lab 4, варіант A9 (Щелочінін Артур): відомі похідні та regression tests.
 * Reference formulas з Додатку A.2 написані тут локально (static),
 * без виклику коду інших варіантів. */
#include <math.h>
#include <stdio.h>

int run_numeric_property_tests(void); /* з tests/test_numeric_properties.c */

static int failures = 0;

static void check(int condition, const char *message) {
    if (!condition) {
        printf("FAIL: %s\n", message);
        failures++;
    }
}

/* Порівняння з tolerance: |actual - expected| <= abs_tol + rel_tol * max(|actual|, |expected|) */
static int near(double actual, double expected, double abs_tol, double rel_tol) {
    return isfinite(actual) && isfinite(expected) &&
           fabs(actual - expected) <= abs_tol + rel_tol * fmax(fabs(actual), fabs(expected));
}

/* ---- reference formulas (A.2) ---- */

static double ref_forward(double (*f)(double), double x, double h) {
    return (f(x + h) - f(x)) / h;
}

static double ref_backward(double (*f)(double), double x, double h) {
    return (f(x) - f(x - h)) / h;
}

static double ref_central(double (*f)(double), double x, double h) {
    return (f(x + h) - f(x - h)) / (2.0 * h);
}

static double square(double x) { return x * x; }
static double cube(double x) { return x * x * x; }

/* Відомі похідні: (x^2)' = 2x, sin'(0) = 1, exp'(0) = 1.
 * Tolerance 1e-7: похибка усічення central при h = 1e-4 приблизно
 * h^2 * |f'''| / 6, тобто близько 2e-9, а округлення близько eps/h, тобто 2e-12.
 * Запас приблизно в 50 разів, щоб тест був переносним. */
static void test_known_derivatives(void) {
    double h = 1e-4;
    double tol = 1e-7;
    check(near(ref_central(square, 2.0, h), 4.0, tol, tol), "(x^2)' at 2 = 4");
    check(near(ref_central(sin, 0.0, h), 1.0, tol, tol), "sin'(0) = 1");
    check(near(ref_central(exp, 0.0, h), 1.0, tol, tol), "exp'(0) = 1");
    check(near(ref_central(cube, 1.0, h), 3.0, tol, tol), "(x^3)' at 1 = 3");
}

/* Regression cases: значення, які формули дають точно (рахується вручну).
 *  forward  x^2, x = 2, h = 0.5:  (6.25 - 4) / 0.5  = 4.5  (= 2x + h)
 *  backward x^2, x = 2, h = 0.5:  (4 - 2.25) / 0.5  = 3.5  (= 2x - h)
 *  central  x^2, x = 2, h = 0.5:  (6.25 - 2.25) / 1 = 4    (для x^2 точно)
 *  central  x^3, x = 1, h = 0.5:  (3.375 - 0.125) / 1 = 3.25 (= 3x^2 + h^2)
 * Усі числа точно представляються в double, тому tolerance мінімальний (1e-12). */
static void test_regression_cases(void) {
    double tol = 1e-12;
    check(near(ref_forward(square, 2.0, 0.5), 4.5, tol, tol), "regression forward x^2");
    check(near(ref_backward(square, 2.0, 0.5), 3.5, tol, tol), "regression backward x^2");
    check(near(ref_central(square, 2.0, 0.5), 4.0, tol, tol), "regression central x^2");
    check(near(ref_central(cube, 1.0, 0.5), 3.25, tol, tol), "regression central x^3");
}

int run_differentiation_tests(void) {
    failures = 0;
    test_known_derivatives();
    test_regression_cases();
    return failures;
}

int main(void) {
    int failed = run_differentiation_tests() + run_numeric_property_tests();
    if (failed != 0) {
        printf("%d Lab 4 A9 checks failed\n", failed);
        return 1;
    }
    printf("All Lab 4 A9 tests passed\n");
    return 0;
}

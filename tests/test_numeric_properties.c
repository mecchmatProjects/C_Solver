/* Lab 4, варіант A9 (Щелочінін Артур): властивості точності різницевих формул.
 *
 * Тут незалежні static reference formulas з Додатку A.2.
 * Публічний API miniai_derivative_* тут навмисно не викликається:
 * це завдання інших варіантів, а тести мають працювати самостійно.
 * Публічний API відхиляє h <= 0, а reference-формули ні, тому
 * на них можна перевірити симетрію з від'ємним h. */
#include <math.h>
#include <stdio.h>

static int failures = 0;

static void check(int condition, const char *message) {
    if (!condition) {
        printf("FAIL: %s\n", message);
        failures++;
    }
}

/* ---- reference formulas (A.2) ---- */

static double ref_forward(double (*f)(double), double x, double h) {
    return (f(x + h) - f(x)) / h;
}

static double ref_central(double (*f)(double), double x, double h) {
    return (f(x + h) - f(x - h)) / (2.0 * h);
}

/* ---- гладкі тестові функції та їх точні похідні ---- */

static double cube(double x) { return x * x * x; }
static double cube_derivative(double x) { return 3.0 * x * x; }

/* Властивість 1: D_c(f, x, h) == D_c(f, x, -h).
 * При заміні h на -h чисельник і знаменник точно змінюють знак
 * (у double заперечення точне), тому результат має збігтися побітово,
 * і tolerance тут не потрібен. */
static void test_central_symmetry(void) {
    double steps[3] = {1e-1, 1e-3, 1e-5};
    for (int i = 0; i < 3; i++) {
        double h = steps[i];
        check(ref_central(sin, 1.0, h) == ref_central(sin, 1.0, -h), "symmetry sin");
        check(ref_central(exp, 0.5, h) == ref_central(exp, 0.5, -h), "symmetry exp");
        check(ref_central(cube, 2.0, h) == ref_central(cube, 2.0, -h), "symmetry x^3");
    }
}

/* Властивість 2: для гладких функцій central точніша за forward
 * при тому самому h (O(h^2) проти O(h)). */
static void test_central_better_than_forward(void) {
    double h = 1e-3;

    double ef = fabs(ref_forward(sin, 1.0, h) - cos(1.0));
    double ec = fabs(ref_central(sin, 1.0, h) - cos(1.0));
    check(ec < ef, "central better than forward: sin at 1");

    ef = fabs(ref_forward(exp, 0.0, h) - 1.0);
    ec = fabs(ref_central(exp, 0.0, h) - 1.0);
    check(ec < ef, "central better than forward: exp at 0");

    ef = fabs(ref_forward(cube, 2.0, h) - cube_derivative(2.0));
    ec = fabs(ref_central(cube, 2.0, h) - cube_derivative(2.0));
    check(ec < ef, "central better than forward: x^3 at 2");
}

/* Властивість 3: порядок точності.
 * Якщо зменшити h удвічі, похибка forward має зменшитись ~у 2 рази (O(h)),
 * а central ~у 4 рази (O(h^2)). Беремо h = 1e-2 і 5e-3: тут ще домінує
 * похибка усічення, а не округлення. Межі [1.8; 2.2] і [3.5; 4.5] широкі,
 * щоб тест не залежав від платформи й компілятора. */
static void test_order_of_accuracy(void) {
    double h = 1e-2;

    double ef1 = fabs(ref_forward(sin, 1.0, h) - cos(1.0));
    double ef2 = fabs(ref_forward(sin, 1.0, h / 2) - cos(1.0));
    double ratio_forward = ef1 / ef2;
    check(ratio_forward > 1.8 && ratio_forward < 2.2, "forward has order O(h)");

    double ec1 = fabs(ref_central(sin, 1.0, h) - cos(1.0));
    double ec2 = fabs(ref_central(sin, 1.0, h / 2) - cos(1.0));
    double ratio_central = ec1 / ec2;
    check(ratio_central > 3.5 && ratio_central < 4.5, "central has order O(h^2)");

    ec1 = fabs(ref_central(exp, 0.0, h) - 1.0);
    ec2 = fabs(ref_central(exp, 0.0, h / 2) - 1.0);
    ratio_central = ec1 / ec2;
    check(ratio_central > 3.5 && ratio_central < 4.5, "central O(h^2) for exp");
}

/* Властивість 4: cancellation. При дуже малому h віднімаються майже
 * рівні числа, і похибка округлення ~eps/h стає більшою за похибку
 * усічення. Тому h = 1e-13 дає гіршу відповідь, ніж h = 1e-5.
 * Різниця між ними кілька порядків, тож тест стабільний на будь-якій платформі. */
static void test_cancellation(void) {
    double good = fabs(ref_central(sin, 1.0, 1e-5) - cos(1.0));
    double bad = fabs(ref_central(sin, 1.0, 1e-13) - cos(1.0));
    check(bad > good, "too small h is worse because of round-off");
}

int run_numeric_property_tests(void) {
    failures = 0;
    test_central_symmetry();
    test_central_better_than_forward();
    test_order_of_accuracy();
    test_cancellation();
    return failures;
}

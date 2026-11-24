#include "miniai/differentiation.h"

#include <assert.h>
#include <float.h>
#include <math.h>
#include <stdio.h>

/* Тестова скалярна функція f(x) = x^2 */
static double sample_square(double x, void *user_data) {
    (void)user_data;
    return x * x;
}

/* Тестова багатовимірна функція f(x) = x[0]^2 */
static double sample_objective(const double *x, size_t n, void *user_data) {
    (void)n;
    (void)user_data;
    return x[0] * x[0];
}

/* Сценарій 1: перевірка стандартних додатних значень кроку */
static void test_valid_steps(void) {
    assert(miniai_is_valid_step(1e-5) == 1);
    assert(miniai_is_valid_step(1.0) == 1);
}

/* Сценарій 2: перевірка граничних скінченних значень double (DBL_MIN та DBL_MAX) */
static void test_boundary_steps(void) {
    assert(miniai_is_valid_step(DBL_MIN) == 1);
    assert(miniai_is_valid_step(DBL_MAX) == 1);
}

/* Сценарій 3: відхилення нуля, від'ємних чисел та спеціальних значень IEEE 754 */
static void test_invalid_steps(void) {
    assert(miniai_is_valid_step(0.0) == 0);
    assert(miniai_is_valid_step(-0.0) == 0);
    assert(miniai_is_valid_step(-1e-5) == 0);
    assert(miniai_is_valid_step(-DBL_MIN) == 0);
    assert(miniai_is_valid_step((double)NAN) == 0);
    assert(miniai_is_valid_step((double)INFINITY) == 0);
    assert(miniai_is_valid_step(-(double)INFINITY) == 0);
}

/* Сценарій 4: перевірка реакції на NULL callback та невалідний крок (NAN / код помилки) */
static void test_null_callbacks_and_errors(void) {
    /* Скалярна функція має повернути NAN при NULL callback або нульовому кроці */
    double res_null = miniai_differentiate_scalar_checked(NULL, 2.0, 1e-5, NULL);
    assert(isnan(res_null));

    double res_bad_h = miniai_differentiate_scalar_checked(sample_square, 2.0, 0.0, NULL);
    assert(isnan(res_bad_h));

    /* Функція градієнта має повернути код != 0 і не змінити буфер grad */
    double x[1] = {3.0};
    double grad[1] = {42.0};
    int status_null_cb = miniai_gradient_checked(NULL, x, 1, 1e-5, grad, NULL);
    assert(status_null_cb != 0);
    assert(grad[0] == 42.0);

    int status_bad_h = miniai_gradient_checked(sample_objective, x, 1, -1.0, grad, NULL);
    assert(status_bad_h != 0);
    assert(grad[0] == 42.0);
}

/* Сценарій 5: перевірка коректного обчислення похідної при валідних даних */
static void test_valid_scalar_derivative_call(void) {
    double d = miniai_differentiate_scalar_checked(sample_square, 3.0, 1e-5, NULL);
    assert(fabs(d - 6.0) < 1e-7);
}

/* Точка входу тестового виконуваного файлу */
int main(void) {
    test_valid_steps();
    test_boundary_steps();
    test_invalid_steps();
    test_null_callbacks_and_errors();
    test_valid_scalar_derivative_call();

    printf("All differentiation validation tests passed.\n");
    return 0;
}
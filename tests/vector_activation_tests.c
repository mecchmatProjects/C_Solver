#include <stdio.h>
#include <stddef.h>
#include <math.h>

extern int miniai_vector_sigmoid(const double in[], double out[], size_t n);

static int failures = 0;
static int checks = 0;

static void expect_near(double actual, double expected, const char* message) {
    ++checks;
    double tolerance = 1e-7 * fmax(1.0, fabs(expected));
    if (!(fabs(actual - expected) <= tolerance)) {
        fprintf(stderr, "FAIL: %s (actual %.17g, expected %.17g)\n", message, actual, expected);
        ++failures;
    }
}

static void expect_int_eq(int actual, int expected, const char* message) {
    ++checks;
    if (actual != expected) {
        fprintf(stderr, "FAIL: %s (actual %d, expected %d)\n", message, actual, expected);
        ++failures;
    }
}

static void test_vector_sigmoid(void) {
    /* 1. Обов'язкова перевірка: [0, 0] -> [0.5, 0.5] */
    {
        const double in[2] = { 0.0, 0.0 };
        double out[2] = { -1.0, -1.0 };
        int rc = miniai_vector_sigmoid(in, out, 2);
        expect_int_eq(rc, 0, "Sigmoid [0, 0] returns status 0");
        expect_near(out[0], 0.5, "Sigmoid(0.0) == 0.5 [0]");
        expect_near(out[1], 0.5, "Sigmoid(0.0) == 0.5 [1]");
    }

    /* 2. Монотонність: при x_0 < x_1 < ... < x_{k-1} маємо out_0 <= out_1 <= ... <= out_{k-1} */
    {
        const double in[5] = { -5.0, -1.0, 0.0, 1.5, 6.0 };
        double out[5] = { 0.0 };
        int rc = miniai_vector_sigmoid(in, out, 5);
        expect_int_eq(rc, 0, "Sigmoid monotonic input returns status 0");
        for (size_t i = 1; i < 5; ++i) {
            ++checks;
            if (!(out[i - 1] < out[i])) {
                fprintf(stderr, "FAIL: Sigmoid not strictly increasing at index %zu (%.17g >= %.17g)\n",
                    i, out[i - 1], out[i]);
                ++failures;
            }
        }
    }

    /* 3. Робота in-place (in та out вказують на один буфер) */
    {
        double buf[3] = { -2.0, 0.0, 2.0 };
        double expected[3] = {
            1.0 / (1.0 + exp(2.0)),
            0.5,
            1.0 / (1.0 + exp(-2.0))
        };
        int rc = miniai_vector_sigmoid(buf, buf, 3);
        expect_int_eq(rc, 0, "Sigmoid in-place returns status 0");
        expect_near(buf[0], expected[0], "Sigmoid in-place [-2.0]");
        expect_near(buf[1], expected[1], "Sigmoid in-place [0.0]");
        expect_near(buf[2], expected[2], "Sigmoid in-place [2.0]");
    }

    /* 4. Граничний випадок: великі додатні та від'ємні x */
    {
        const double in[2] = { -1000.0, 1000.0 };
        double out[2] = { -1.0, -1.0 };
        int rc = miniai_vector_sigmoid(in, out, 2);
        expect_int_eq(rc, 0, "Sigmoid large +-x returns status 0");
        expect_near(out[0], 0.0, "Sigmoid(-1000) approaches 0.0");
        expect_near(out[1], 1.0, "Sigmoid(+1000) approaches 1.0");
    }

    /* 5. Граничний випадок: n = 0 */
    {
        const double in[1] = { 1.0 };
        double out[1] = { 42.0 };
        int rc = miniai_vector_sigmoid(in, out, 0);
        expect_int_eq(rc, 0, "Sigmoid with n=0 returns status 0");
        expect_near(out[0], 42.0, "Sigmoid with n=0 does not modify out");
    }

    /* 6. Некоректні вказівники при n > 0 */
    {
        double out[1] = { 0.0 };
        int rc = miniai_vector_sigmoid(NULL, out, 1);
        ++checks;
        if (rc == 0) {
            fprintf(stderr, "FAIL: Sigmoid with NULL input and n>0 should return error\n");
            ++failures;
        }
    }
}

int main(void) {
    test_vector_sigmoid();

    if (failures > 0) {
        fprintf(stderr, "FAILURE: %d of %d checks failed.\n", failures, checks);
        return 1;
    }

    printf("SUCCESS: All %d checks passed.\n", checks);
    return 0;
}
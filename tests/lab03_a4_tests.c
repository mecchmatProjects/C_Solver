#include <math.h>
#include <stddef.h>
#include <stdio.h>

#include "miniai/math/vector.h"

static int failures = 0;
static int checks = 0;

static void expect_true(int condition, const char *message) {
    ++checks;
    if (!condition) {
        fprintf(stderr, "FAIL: %s\n", message);
        ++failures;
    }
}

static void expect_array_near(const double actual[], const double expected[],
                              size_t n, const char *message) {
    ++checks;
    for (size_t i = 0; i < n; ++i) {
        if (!(fabs(actual[i] - expected[i]) <= 1e-12)) {
            fprintf(stderr,
                    "FAIL: %s at index %zu (actual %.17g, expected %.17g)\n",
                    message, i, actual[i], expected[i]);
            ++failures;
            return;
        }
    }
}

static void test_scale_alphas(void) {
    const double in[4] = {-2.5, 0.0, 1.5, 4.0};
    double out[4] = {0.0};

    /* 1. alpha = 2.0 */
    const double expected_pos[4] = {-5.0, 0.0, 3.0, 8.0};
    expect_true(miniai_vector_scale(in, 2.0, out, 4) == 0,
                "scale with alpha = 2.0 returns 0");
    expect_array_near(out, expected_pos, 4, "scale with alpha = 2.0 values");

    /* 2. alpha = 0.0 */
    const double expected_zero[4] = {0.0, 0.0, 0.0, 0.0};
    expect_true(miniai_vector_scale(in, 0.0, out, 4) == 0,
                "scale with alpha = 0.0 returns 0");
    expect_array_near(out, expected_zero, 4, "scale with alpha = 0.0 values");

    /* 3. alpha = -1.0 */
    const double expected_neg[4] = {2.5, 0.0, -1.5, -4.0};
    expect_true(miniai_vector_scale(in, -1.0, out, 4) == 0,
                "scale with alpha = -1.0 returns 0");
    expect_array_near(out, expected_neg, 4, "scale with alpha = -1.0 values");
}

static void test_scale_inplace(void) {
    /* 4. Режим in-place (in == out) */
    double data[3] = {1.0, -3.0, 2.5};
    const double expected[3] = {2.0, -6.0, 5.0};

    expect_true(miniai_vector_scale(data, 2.0, data, 3) == 0,
                "in-place scale returns 0");
    expect_array_near(data, expected, 3, "in-place scale values");
}

static void test_scale_edge_cases(void) {
    const double in[2] = {1.0, 2.0};
    double out[2] = {9.0, 9.0};

    /* 5. n = 0 (не змінює буфер і не звертається до NULL) */
    expect_true(miniai_vector_scale(in, 5.0, out, 0) == 0,
                "n = 0 with valid pointers returns 0");
    expect_true(out[0] == 9.0 && out[1] == 9.0,
                "n = 0 does not modify output buffer");
    expect_true(miniai_vector_scale(NULL, 5.0, NULL, 0) == 0,
                "n = 0 with NULL pointers returns 0");

    /* 6. NULL при n > 0 повертає ненульовий код помилки */
    expect_true(miniai_vector_scale(NULL, 2.0, out, 2) != 0,
                "NULL input with n > 0 returns nonzero");
    expect_true(miniai_vector_scale(in, 2.0, NULL, 2) != 0,
                "NULL output with n > 0 returns nonzero");
}

int main(void) {
    test_scale_alphas();
    test_scale_inplace();
    test_scale_edge_cases();

    if (failures != 0) {
        fprintf(stderr, "lab03_a4_tests: %d/%d checks failed\n", failures,
                checks);
        return 1;
    }

    printf("lab03_a4_tests: all %d checks passed\n", checks);
    return 0;
}
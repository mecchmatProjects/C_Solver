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

static void test_relu_values(void) {
    const double input[] = {-2.0, 0.0, 3.0};
    double output[3] = {-1.0, -1.0, -1.0};

    expect_true(miniai_vector_relu(input, output, 3) == 0,
                "apply vector ReLU");
    expect_true(output[0] == 0.0 && output[1] == 0.0 && output[2] == 3.0,
                "map [-2, 0, 3] to [0, 0, 3]");
}

static void test_single_element(void) {
    const double input[] = {-4.0};
    double output[] = {7.0};

    expect_true(miniai_vector_relu(input, output, 1) == 0,
                "apply ReLU to one element");
    expect_true(output[0] == 0.0, "negative singleton maps to zero");
}

static void test_in_place(void) {
    double values[] = {-1.0, 2.0, 0.0};

    expect_true(miniai_vector_relu(values, values, 3) == 0,
                "support in-place vector ReLU");
    expect_true(values[0] == 0.0 && values[1] == 2.0 && values[2] == 0.0,
                "in-place output is correct");
}

static void test_empty_and_invalid_arguments(void) {
    const double input[] = {1.0};
    double output[] = {42.0};

    expect_true(miniai_vector_relu(NULL, NULL, 0) == 0,
                "accept empty vectors without pointers");
    expect_true(output[0] == 42.0,
                "empty vector leaves output untouched");
    expect_true(miniai_vector_relu(NULL, output, 1) != 0,
                "reject null input for nonempty vector");
    expect_true(miniai_vector_relu(input, NULL, 1) != 0,
                "reject null output for nonempty vector");
    expect_true(output[0] == 42.0,
                "invalid input leaves output untouched");
}

int main(void) {
    test_relu_values();
    test_single_element();
    test_in_place();
    test_empty_and_invalid_arguments();

    if (failures != 0) {
        fprintf(stderr, "%d of %d vector activation checks failed\n", failures,
                checks);
        return 1;
    }

    printf("%d vector activation checks passed\n", checks);
    return 0;
}
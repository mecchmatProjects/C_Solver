#include <math.h>
#include <stdio.h>

#include "miniai/ml/activation/activations.h"

static int failures = 0;
static int checks = 0;

static void expect_near(double actual, double expected, const char *message) {
    ++checks;
    if (!(fabs(actual - expected) <= 1e-12)) {
        fprintf(stderr, "FAIL: %s (actual %.17g, expected %.17g)\n", message,
                actual, expected);
        ++failures;
    }
}

static void expect_status(ActivationStatus actual, ActivationStatus expected,
                          const char *message) {
    ++checks;
    if (actual != expected) {
        fprintf(stderr, "FAIL: %s (status %d, expected %d)\n", message,
                (int)actual, (int)expected);
        ++failures;
    }
}

static void expect_finite(double actual, const char *message) {
    ++checks;
    if (!isfinite(actual)) {
        fprintf(stderr, "FAIL: %s returned a non-finite result\n", message);
        ++failures;
    }
}

static void test_relu(void) {
    Activation activation;
    double value;
    double derivative;

    expect_status(activation_relu_init(&activation), ACTIVATION_STATUS_OK,
                  "initialize ReLU");
    expect_status(activation_value(&activation, -2.0, &value),
                  ACTIVATION_STATUS_OK, "evaluate ReLU");
    expect_near(value, 0.0, "ReLU negative value");
    expect_status(activation_value(&activation, 3.0, &value),
                  ACTIVATION_STATUS_OK, "evaluate positive ReLU");
    expect_near(value, 3.0, "ReLU positive value");
    expect_status(activation_derivative(&activation, 0.0, &derivative),
                  ACTIVATION_STATUS_OK, "differentiate ReLU");
    expect_near(derivative, 0.0, "ReLU derivative at zero");
    expect_status(activation_derivative(&activation, 2.0, &derivative),
                  ACTIVATION_STATUS_OK, "differentiate positive ReLU");
    expect_near(derivative, 1.0, "ReLU positive derivative");
}

static void test_leaky_relu(void) {
    Activation activation;
    double value;
    double derivative;

    expect_status(activation_leaky_relu_init(&activation, 0.1),
                  ACTIVATION_STATUS_OK, "initialize LeakyReLU");
    expect_status(activation_value(&activation, -2.0, &value),
                  ACTIVATION_STATUS_OK, "evaluate LeakyReLU");
    expect_near(value, -0.2, "LeakyReLU negative value");
    expect_status(activation_derivative(&activation, -2.0, &derivative),
                  ACTIVATION_STATUS_OK, "differentiate LeakyReLU");
    expect_near(derivative, 0.1, "LeakyReLU negative derivative");
    expect_status(activation_derivative(&activation, 0.0, &derivative),
                  ACTIVATION_STATUS_OK, "differentiate LeakyReLU at zero");
    expect_near(derivative, 1.0, "LeakyReLU derivative at zero");
    expect_status(activation_leaky_relu_init(&activation, -0.1),
                  ACTIVATION_STATUS_INVALID_ARGUMENT,
                  "reject negative LeakyReLU slope");
    expect_status(activation_leaky_relu_init(&activation, INFINITY),
                  ACTIVATION_STATUS_INVALID_ARGUMENT,
                  "reject infinite LeakyReLU slope");
    expect_status(activation_leaky_relu_init(NULL, 0.1),
                  ACTIVATION_STATUS_INVALID_ARGUMENT,
                  "reject null LeakyReLU output");
}

static void test_elu(void) {
    Activation activation;
    double value;
    double derivative;

    expect_status(activation_elu_init(&activation, 1.0), ACTIVATION_STATUS_OK,
                  "initialize ELU");
    expect_status(activation_value(&activation, -1.0, &value),
                  ACTIVATION_STATUS_OK, "evaluate ELU");
    expect_near(value, exp(-1.0) - 1.0, "ELU negative value");
    expect_status(activation_value(&activation, 2.0, &value),
                  ACTIVATION_STATUS_OK, "evaluate positive ELU");
    expect_near(value, 2.0, "ELU positive value");
    expect_status(activation_derivative(&activation, -1.0, &derivative),
                  ACTIVATION_STATUS_OK, "differentiate ELU");
    expect_near(derivative, exp(-1.0), "ELU negative derivative");
    expect_status(activation_elu_init(&activation, -1.0),
                  ACTIVATION_STATUS_INVALID_ARGUMENT, "reject negative ELU alpha");
    expect_status(activation_elu_init(&activation, NAN),
                  ACTIVATION_STATUS_INVALID_ARGUMENT, "reject NaN ELU alpha");
}

static void test_sigmoid(void) {
    Activation activation;
    double value;
    double derivative;

    expect_status(activation_sigmoid_init(&activation), ACTIVATION_STATUS_OK,
                  "initialize Sigmoid");
    expect_status(activation_value(&activation, 0.0, &value),
                  ACTIVATION_STATUS_OK, "evaluate Sigmoid at zero");
    expect_near(value, 0.5, "Sigmoid at zero");
    expect_status(activation_value(&activation, 1000.0, &value),
                  ACTIVATION_STATUS_OK, "evaluate Sigmoid at large input");
    expect_near(value, 1.0, "Sigmoid large positive input");
    expect_status(activation_value(&activation, -1000.0, &value),
                  ACTIVATION_STATUS_OK, "evaluate Sigmoid at negative input");
    expect_near(value, 0.0, "Sigmoid large negative input");
    expect_status(activation_derivative(&activation, 0.0, &derivative),
                  ACTIVATION_STATUS_OK, "differentiate Sigmoid");
    expect_near(derivative, 0.25, "Sigmoid derivative at zero");
}

static void test_sigmweight(void) {
    Activation activation;
    double value;
    double derivative;

    expect_status(activation_sigmweight_init(&activation), ACTIVATION_STATUS_OK,
                  "initialize Sigmweight");
                  
    expect_status(activation_value(&activation, 0.0, &value),
                  ACTIVATION_STATUS_OK, "evaluate Sigmweight at zero");
    expect_near(value, 0.0, "Sigmweight at zero");
    
    expect_status(activation_value(&activation, 1000.0, &value),
                  ACTIVATION_STATUS_OK, "evaluate Sigmweight at large input");
    expect_near(value, 1000.0, "Sigmweight large positive input");
    
    expect_status(activation_value(&activation, -1000.0, &value),
                  ACTIVATION_STATUS_OK, "evaluate Sigmweight at negative input");
    expect_near(value, 0.0, "Sigmweight large negative input");
    
    expect_status(activation_derivative(&activation, 0.0, &derivative),
                  ACTIVATION_STATUS_OK, "differentiate Sigmweight");
    expect_near(derivative, 0.5, "Sigmweight derivative at zero");
}

static void test_softplus(void) {
    Activation activation;
    double value;
    double derivative;

    expect_status(activation_softplus_init(&activation), ACTIVATION_STATUS_OK,
                  "initialize SoftPlus");
    expect_status(activation_value(&activation, 0.0, &value),
                  ACTIVATION_STATUS_OK, "evaluate SoftPlus at zero");
    expect_near(value, log(2.0), "SoftPlus at zero");
    expect_status(activation_value(&activation, 1000.0, &value),
                  ACTIVATION_STATUS_OK, "evaluate SoftPlus at large input");
    expect_near(value, 1000.0, "SoftPlus large input");
    expect_status(activation_value(&activation, -1000.0, &value),
                  ACTIVATION_STATUS_OK, "evaluate SoftPlus at small input");
    expect_near(value, 0.0, "SoftPlus small input");
    expect_status(activation_derivative(&activation, 0.0, &derivative),
                  ACTIVATION_STATUS_OK, "differentiate SoftPlus");
    expect_near(derivative, 0.5, "SoftPlus derivative at zero");
}

static void test_softsign(void) {
    Activation activation;
    double value;
    double derivative;

    expect_status(activation_softsign_init(&activation), ACTIVATION_STATUS_OK,
                  "initialize SoftSign");
    expect_status(activation_value(&activation, 2.0, &value),
                  ACTIVATION_STATUS_OK, "evaluate SoftSign");
    expect_near(value, 2.0 / 3.0, "SoftSign positive value");
    expect_status(activation_value(&activation, -2.0, &value),
                  ACTIVATION_STATUS_OK, "evaluate negative SoftSign");
    expect_near(value, -2.0 / 3.0, "SoftSign negative value");
    expect_status(activation_derivative(&activation, 0.0, &derivative),
                  ACTIVATION_STATUS_OK, "differentiate SoftSign at zero");
    expect_near(derivative, 1.0, "SoftSign derivative at zero");
    expect_status(activation_derivative(&activation, 2.0, &derivative),
                  ACTIVATION_STATUS_OK, "differentiate SoftSign");
    expect_near(derivative, 1.0 / 9.0, "SoftSign derivative");
}

static void test_gaussian(void) {
    Activation activation;
    double value;
    double derivative;

    expect_status(activation_gaussian_init(&activation), ACTIVATION_STATUS_OK,
                  "initialize Gaussian");
    expect_status(activation_value(&activation, 0.0, &value),
                  ACTIVATION_STATUS_OK, "evaluate Gaussian at zero");
    expect_near(value, 1.0, "Gaussian at zero");
    expect_status(activation_value(&activation, 1.0, &value),
                  ACTIVATION_STATUS_OK, "evaluate Gaussian at one");
    expect_near(value, exp(-1.0), "Gaussian at one");
    expect_status(activation_derivative(&activation, 0.0, &derivative),
                  ACTIVATION_STATUS_OK, "differentiate Gaussian at zero");
    expect_near(derivative, 0.0, "Gaussian derivative at zero");
    expect_status(activation_derivative(&activation, 1.0, &derivative),
                  ACTIVATION_STATUS_OK, "differentiate Gaussian");
    expect_near(derivative, -2.0 * exp(-1.0), "Gaussian derivative at one");
}

static void test_bent(void) {
    Activation activation;
    double value;
    double derivative;
    const double root_two = sqrt(2.0);

    expect_status(activation_bent_init(&activation), ACTIVATION_STATUS_OK,
                  "initialize Bent");
    expect_status(activation_value(&activation, 0.0, &value),
                  ACTIVATION_STATUS_OK, "evaluate Bent at zero");
    expect_near(value, 0.0, "Bent at zero");
    expect_status(activation_value(&activation, 1.0, &value),
                  ACTIVATION_STATUS_OK, "evaluate positive Bent");
    expect_near(value, 1.0 + 0.5 * (root_two - 1.0),
                "Bent positive value");
    expect_status(activation_value(&activation, -1.0, &value),
                  ACTIVATION_STATUS_OK, "evaluate negative Bent");
    expect_near(value, -1.0 + 0.5 * (root_two - 1.0),
                "Bent negative value");
    expect_status(activation_derivative(&activation, 0.0, &derivative),
                  ACTIVATION_STATUS_OK, "differentiate Bent at zero");
    expect_near(derivative, 1.0, "Bent derivative at zero");
    expect_status(activation_derivative(&activation, 1.0, &derivative),
                  ACTIVATION_STATUS_OK, "differentiate positive Bent");
    expect_near(derivative, 1.0 + 0.5 / root_two,
                "Bent positive derivative");
    expect_status(activation_derivative(&activation, -1.0, &derivative),
                  ACTIVATION_STATUS_OK, "differentiate negative Bent");
    expect_near(derivative, 1.0 - 0.5 / root_two,
                "Bent negative derivative");
    expect_status(activation_bent_init(NULL),
                  ACTIVATION_STATUS_INVALID_ARGUMENT,
                  "reject null Bent output");
}

#ifdef MINIAI_ENABLE_INVSQRT
static void test_invsqrt(void) {
    Activation activation;
    double value;
    double derivative;
  
    expect_status(activation_invsqrt_init(&activation, 1.0), ACTIVATION_STATUS_OK,
                  "initialize invsqrt");
    expect_status(activation_value(&activation, 0.0, &value),
                  ACTIVATION_STATUS_OK, "evaluate invsqrt at zero");
    expect_near(value, 0.0, "invsqrt at zero");
    expect_status(activation_value(&activation, 1.0, &value),
                  ACTIVATION_STATUS_OK, "evaluate invsqrt at one");
    expect_near(value, 1/sqrt(2), "invsqrt at one");
    expect_status(activation_derivative(&activation, 0.0, &derivative),
                  ACTIVATION_STATUS_OK, "differentiate invsqrt at zero");
    expect_near(derivative, 1.0, "invsqrt derivative at zero");
    expect_status(activation_derivative(&activation, 1.0, &derivative),
                  ACTIVATION_STATUS_OK, "differentiate invsqrt at one");
    expect_near(derivative, 1/(2*sqrt(2)), "invsqrt derivative at one");
}
#endif


#ifdef MINIAI_ENABLE_ARCTAN_TESTS
static void test_arctan(void) {
    Activation activation;
    double value;
    double derivative;
  
    expect_status(activation_arctan_init(&activation), ACTIVATION_STATUS_OK,
                  "initialize Arctan");
    expect_status(activation_value(&activation, 0.0, &value),
                  ACTIVATION_STATUS_OK, "evaluate Arctan at zero");
    expect_near(value, 0.0, "Arctan at zero");
    expect_status(activation_value(&activation, 1.0, &value),
                  ACTIVATION_STATUS_OK, "evaluate Arctan at one");
    expect_near(value, atan(1.0), "Arctan at one");
    expect_status(activation_value(&activation, INFINITY, &value),
                  ACTIVATION_STATUS_OK, "evaluate Arctan at infinity");
    expect_near(value, acos(-1.0) / 2.0, "Arctan at infinity");
    expect_status(activation_derivative(&activation, 0.0, &derivative),
                  ACTIVATION_STATUS_OK, "differentiate Arctan at zero");
    expect_near(derivative, 1.0, "Arctan derivative at zero");
    expect_status(activation_derivative(&activation, 1.0, &derivative),
                  ACTIVATION_STATUS_OK, "differentiate Arctan at one");
    expect_near(derivative, 0.5, "Arctan derivative at one");
    expect_status(activation_arctan_init(NULL),
                  ACTIVATION_STATUS_INVALID_ARGUMENT,
                  "reject null Arctan output");
}
#endif

static void test_dispatch_validation(void) {
    Activation activation;
    double result = 123.0;
    const ActivationVTable invalid_vtable = {NULL, NULL};
    const Activation invalid_activation = {&invalid_vtable, 0.0};

    expect_status(activation_relu_init(&activation), ACTIVATION_STATUS_OK,
                  "initialize activation for argument validation");
    expect_status(activation_relu_init(NULL), ACTIVATION_STATUS_INVALID_ARGUMENT,
                  "reject null activation initializer");
    expect_status(activation_value(NULL, 0.0, &result),
                  ACTIVATION_STATUS_INVALID_ARGUMENT,
                  "reject null activation value input");
    expect_status(activation_value(&invalid_activation, 0.0, &result),
                  ACTIVATION_STATUS_INVALID_ARGUMENT,
                  "reject missing activation value callback");
    expect_status(activation_derivative(&invalid_activation, 0.0, &result),
                  ACTIVATION_STATUS_INVALID_ARGUMENT,
                  "reject missing activation derivative callback");
    expect_status(activation_value(&activation, 0.0, NULL),
                  ACTIVATION_STATUS_INVALID_ARGUMENT,
                  "reject null activation result");
    expect_near(result, 123.0, "invalid activation call preserves result");
}

static void test_polymorphic_interface(void) {
    Activation activations[4];
    ActivationStatus statuses[4];
    double value;
    double derivative;
    size_t index;

    statuses[0] = activation_relu_init(&activations[0]);
    statuses[1] = activation_sigmoid_init(&activations[1]);
    statuses[2] = activation_gaussian_init(&activations[2]);
    statuses[3] = activation_bent_init(&activations[3]);
    for (index = 0; index < 4; ++index) {
        expect_status(statuses[index], ACTIVATION_STATUS_OK,
                      "initialize polymorphic activation");
        expect_status(activation_value(&activations[index], 0.5, &value),
                      ACTIVATION_STATUS_OK, "dispatch activation value");
        expect_status(activation_derivative(&activations[index], 0.5,
                                            &derivative),
                      ACTIVATION_STATUS_OK, "dispatch activation derivative");
        expect_finite(value, "activation value");
        expect_finite(derivative, "activation derivative");
    }
}

int main(void) {
    test_relu();
    test_leaky_relu();
    test_elu();
    test_sigmoid();
    test_sigmweight();
    test_softplus();
    test_softsign();
    test_gaussian();
    test_bent();
#ifdef MINIAI_ENABLE_INVSQRT
    test_invsqrt();
#else
    fputs("NOT VALIDATED: InvSqrt (Lab 2 A3)\n", stderr);
#endif
#ifdef MINIAI_ENABLE_ARCTAN_TESTS
    test_arctan();
#else
    fputs("NOT VALIDATED: Arctan (Lab 2 A7)\n", stderr);
#endif
    test_dispatch_validation();
    test_polymorphic_interface();

    if (failures != 0) {
        fprintf(stderr, "%d of %d activation checks failed\n", failures, checks);
        return 1;
    }

    printf("%d activation checks passed\n", checks);
    return 0;
}

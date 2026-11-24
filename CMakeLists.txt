cmake_minimum_required(VERSION 3.16)

project(MiniAI VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

include(CTest)


option(MINIAI_ENABLE_ARCTAN_TESTS "Run pending Arctan tests (Lab 2 A7)" OFF)
option(MINIAI_ENABLE_LOSS_INTEGRATION "Build Lab 2 B10 loss integration tests and demo (requires scalar loss implementations)" OFF)
option(MINIAI_ENABLE_VECTOR_MSE_TESTS "Build Lab 3 B10 tests (requires Lab 2 B2 miniai_squared_error)" OFF)

add_library(miniai
    src/ml/activation/invsqrt.c
    src/math/vector.c
    src/ml/loss/vector_loss.c
    src/math/statistics.c
    src/ml/activation/activation.c
    src/ml/activation/bent.c
    src/ml/activation/arctan.c
    src/ml/activation/elu.c
    src/ml/activation/gaussian.c
    src/ml/activation/leaky_relu.c
    src/ml/activation/relu.c
    src/ml/activation/s_relu.c
    src/ml/activation/sigmoid.c
    src/ml/activation/sigmweight.c
    src/ml/activation/softplus.c
    src/ml/activation/soft_exponential.c
    src/ml/activation/softsign.c
    include/miniai/ml/activation/onestep.h
    src/ml/activation/onestep.c
    src/ml/loss/binary_cross_entropy.c
    src/ml/loss/absolute_error.c
    src/ml/loss/huber.c
    src/math/vector.c
    src/math/statistics.c
    include/miniai/math/statistics.h
    src/ml/activation/sinc.c
    src/ml/activation/tanh_activation.c
    src/ml/activation/linear.c
)
add_library(miniai::miniai ALIAS miniai)



if(NOT MINIAI_ENABLE_ARCTAN_TESTS)
    message(WARNING "Arctan is not validated: pending tests excluded until Lab 2 A7.")
endif()

if(UNIX AND NOT APPLE)
    target_link_libraries(miniai PUBLIC m)
endif()

target_include_directories(miniai
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

add_executable(miniai_cli src/main.c)
target_link_libraries(miniai_cli PRIVATE miniai::miniai)

if(MINIAI_ENABLE_LOSS_INTEGRATION)
    add_executable(miniai_loss_demo examples/loss_demo.c)
    target_link_libraries(miniai_loss_demo PRIVATE miniai::miniai)
endif()

if(BUILD_TESTING)
    add_executable(miniai_lab03_a1_tests tests/lab03_a1_tests.c)
    target_link_libraries(miniai_lab03_a1_tests PRIVATE miniai::miniai)
    add_test(NAME miniai_lab03_a1_tests COMMAND miniai_lab03_a1_tests)
    add_executable(miniai_activation_tests tests/activation_tests.c)
    target_link_libraries(miniai_activation_tests PRIVATE miniai::miniai)
    add_test(NAME miniai_activation_tests COMMAND miniai_activation_tests)
    set_tests_properties(miniai_activation_tests PROPERTIES TIMEOUT 15)
    add_executable(miniai_lab03_a3_tests tests/lab03_a3_tests.c)
    target_link_libraries(miniai_lab03_a3_tests PRIVATE miniai::miniai)
    add_test(NAME miniai_lab03_a3_tests COMMAND miniai_lab03_a3_tests)
        add_executable(miniai_vector_activation_tests tests/vector_activation_tests.c)
        target_link_libraries(miniai_vector_activation_tests PRIVATE miniai::miniai)
        add_test(NAME miniai_vector_activation_tests COMMAND miniai_vector_activation_tests)
    if(MINIAI_ENABLE_INVSQRT)
        target_compile_definitions(miniai_activation_tests PRIVATE MINIAI_ENABLE_INVSQRT)
    endif()
    if(MINIAI_ENABLE_ARCTAN_TESTS)
        target_compile_definitions(miniai_activation_tests PRIVATE MINIAI_ENABLE_ARCTAN_TESTS)
    endif()

    add_executable(miniai_header_tests tests/header_tests.c)
    target_link_libraries(miniai_header_tests PRIVATE miniai::miniai)
    add_test(NAME miniai_header_tests COMMAND miniai_header_tests)
    add_test(NAME miniai_cli_smoke COMMAND miniai_cli)

    if(MINIAI_ENABLE_LOSS_INTEGRATION)
        add_executable(miniai_loss_integration_tests tests/loss_integration_tests.c)
        target_link_libraries(miniai_loss_integration_tests PRIVATE miniai::miniai)
        add_test(NAME miniai_loss_integration_tests COMMAND miniai_loss_integration_tests)
        add_test(NAME miniai_loss_demo COMMAND miniai_loss_demo)
    endif()
    add_executable(miniai_bce_derivative_tests tests/bce_derivative_tests.c)
    target_link_libraries(miniai_bce_derivative_tests PRIVATE miniai::miniai)
    add_test(NAME miniai_bce_derivative_tests COMMAND miniai_bce_derivative_tests)

    add_executable(miniai_invsqrt_tests tests/invsqrt_tests.c)
    target_link_libraries(miniai_invsqrt_tests PRIVATE miniai::miniai)
    add_test(NAME miniai_invsqrt_tests COMMAND miniai_invsqrt_tests)

    add_executable(miniai_onestep_tests tests/onestep_tests.c)
    target_link_libraries(miniai_onestep_tests PRIVATE miniai::miniai)
    add_test(NAME miniai_onestep_tests COMMAND miniai_onestep_tests)

    add_executable(miniai_onestep_demo examples/onestep_demo.c)
    target_link_libraries(miniai_onestep_demo PRIVATE miniai::miniai)
    add_test(NAME miniai_onestep_demo_smoke COMMAND miniai_onestep_demo)

    if(MINIAI_ENABLE_VECTOR_MSE_TESTS)
        add_executable(miniai_lab03_b10_tests tests/lab03_b10_tests.c)
        target_link_libraries(miniai_lab03_b10_tests PRIVATE miniai::miniai)
        add_test(NAME miniai_lab03_b10_tests COMMAND miniai_lab03_b10_tests)
    else()
        message(STATUS
            "Lab 3 B10 tests are disabled; enable MINIAI_ENABLE_VECTOR_MSE_TESTS "
            "after Lab 2 B2 is available."
        )
    endif()

    add_executable(miniai_lab03_a2_tests tests/lab03_a2_tests.c)
    target_link_libraries(miniai_lab03_a2_tests PRIVATE miniai::miniai)
    add_test(NAME miniai_lab03_a2_tests COMMAND miniai_lab03_a2_tests)

    add_executable(miniai_vector_add_demo examples/vector_add_demo.c)
    target_link_libraries(miniai_vector_add_demo PRIVATE miniai::miniai)
    add_test(NAME miniai_vector_add_demo_smoke COMMAND miniai_vector_add_demo)

    add_executable(miniai_lab02_b4_tests tests/lab02_b4_tests.c)
    target_link_libraries(miniai_lab02_b4_tests PRIVATE miniai::miniai)
    add_test(NAME miniai_lab02_b4_tests COMMAND miniai_lab02_b4_tests)

    add_executable(miniai_lab02_b8_tests tests/lab02_b8_tests.c)
    target_link_libraries(miniai_lab02_b8_tests PRIVATE miniai::miniai)
    add_test(NAME miniai_lab02_b8_tests COMMAND miniai_lab02_b8_tests)
    add_executable(miniai_lab03_b7_tests tests/lab03_b7_tests.c)
    target_link_libraries(miniai_lab03_b7_tests PRIVATE miniai::miniai)
    add_test(NAME miniai_lab03_b7_tests COMMAND miniai_lab03_b7_tests)
    add_executable(miniai_absolute_error_derivative_tests tests/absolute_error_derivative_tests.c
            tests/absolute_error_derivative_tests.c)
    target_link_libraries(miniai_absolute_error_derivative_tests PRIVATE miniai::miniai)
    add_test(NAME miniai_absolute_error_derivative_tests COMMAND miniai_absolute_error_derivative_tests)
    add_executable(miniai_mean_tests tests/miniai_mean_tests.c)
    target_link_libraries(miniai_mean_tests PRIVATE miniai::miniai)
    add_test(NAME miniai_mean_tests COMMAND miniai_mean_tests)
    set_tests_properties(miniai_mean_tests PROPERTIES TIMEOUT 15)

    add_executable(miniai_lab03_b4_tests tests/lab03_b4_tests.c)
    target_link_libraries(miniai_lab03_b4_tests PRIVATE miniai::miniai)
    add_test(NAME miniai_lab03_b4_tests COMMAND miniai_lab03_b4_tests)

    add_executable(miniai_lab03_b5_tests tests/lab03_b5_tests.c
            tests/lab03_b5_tests.c)
    target_link_libraries(miniai_lab03_b5_tests PRIVATE miniai::miniai)
    add_test(NAME miniai_lab03_b5_tests COMMAND miniai_lab03_b5_tests)
    add_executable(lab03_a8_tests tests/lab03_a8_tests.c)
    target_link_libraries(lab03_a8_tests PRIVATE miniai::miniai)
    add_test(NAME lab03_a8_tests COMMAND lab03_a8_tests)
    add_executable(sinc_tests tests/sinc_tests.c)
    target_link_libraries(sinc_tests PRIVATE miniai::miniai)
    add_test(NAME sinc_tests COMMAND sinc_tests)
    
    add_executable(miniai_lab03_a4_tests tests/lab03_a4_tests.c)
    target_link_libraries(miniai_lab03_a4_tests PRIVATE miniai::miniai)
    add_test(NAME miniai_lab03_a4_tests COMMAND miniai_lab03_a4_tests)

    add_executable(miniai_loss_header_compile tests/loss_header_compile.c)
    target_include_directories(miniai_loss_header_compile PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
    add_test(NAME miniai_loss_header_compile COMMAND miniai_loss_header_compile)

    add_executable(miniai_loss_contract_tests tests/loss_contract_tests.c)
    target_link_libraries(miniai_loss_contract_tests PRIVATE miniai::miniai)
    add_test(NAME miniai_loss_contract_tests COMMAND miniai_loss_contract_tests)

    add_executable(miniai_tanh_tests tests/tanh_activation_tests.c)
    target_link_libraries(miniai_tanh_tests PRIVATE miniai::miniai)
    add_test(NAME miniai_tanh_tests COMMAND miniai_tanh_tests)

    add_executable(miniai_lab03_a6_tests tests/lab03_a6_tests.c)
    target_link_libraries(miniai_lab03_a6_tests PRIVATE miniai::miniai)
    add_test(NAME miniai_lab03_a6_tests COMMAND miniai_lab03_a6_tests)

    add_executable(miniai_linear_tests tests/linear_tests.c)
    target_link_libraries(miniai_linear_tests PRIVATE miniai::miniai)
    add_test(NAME miniai_linear_tests COMMAND miniai_linear_tests)

    add_executable(miniai_linear_demo examples/linear_demo.c)
    target_link_libraries(miniai_linear_demo PRIVATE miniai::miniai)
    add_test(NAME miniai_linear_demo_smoke COMMAND miniai_linear_demo)
endif()

add_executable(miniai_absolute_error_demo examples/absolute_error_demo.c)
target_link_libraries(miniai_absolute_error_demo PRIVATE miniai::miniai)
add_test(NAME miniai_absolute_error_demo COMMAND miniai_absolute_error_demo)

add_executable(miniai_population_variance_demo examples/population_variance_demo.c)
target_link_libraries(miniai_population_variance_demo PRIVATE miniai::miniai)
add_test(NAME miniai_population_variance_demo COMMAND miniai_population_variance_demo)


add_executable(miniai_stddev_demo examples/stddev_demo.c
        examples/stddev_demo.c)
target_link_libraries(miniai_stddev_demo PRIVATE miniai::miniai)
add_test(NAME miniai_stddev_demo COMMAND miniai_stddev_demo)

cmake_minimum_required(VERSION 3.16)

project(MiniAI VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

include(CTest)

add_library(miniai
    src/ml/activation/activation.c
    src/ml/activation/elu.c
    src/ml/activation/gaussian.c
    src/ml/activation/leaky_relu.c
    src/ml/activation/relu.c
    src/ml/activation/sigmoid.c
    src/ml/activation/softplus.c
    src/ml/activation/softsign.c
    src/ml/activation/invsqrt.c
)
add_library(miniai::miniai ALIAS miniai)

target_include_directories(miniai
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

add_executable(miniai_cli src/main.c)
target_link_libraries(miniai_cli PRIVATE miniai::miniai)

if(BUILD_TESTING)
    add_executable(miniai_activation_tests tests/activation_tests.c)
    target_link_libraries(miniai_activation_tests PRIVATE miniai::miniai)
    add_test(NAME miniai_activation_tests COMMAND miniai_activation_tests)
endif()

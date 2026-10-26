cmake_minimum_required(VERSION 3.16)

project(MiniAI VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

include(CTest)

option(MINIAI_ENABLE_INVSQRT "Build unfinished InvSqrt and its tests (Lab 2 A3)" OFF)
option(MINIAI_ENABLE_ARCTAN_TESTS "Run pending Arctan tests (Lab 2 A7)" OFF)

add_library(miniai
    src/ml/activation/activation.c
    src/ml/activation/bent.c
    src/ml/activation/arctan.c
    src/ml/activation/elu.c
    src/ml/activation/gaussian.c
    src/ml/activation/leaky_relu.c
    src/ml/activation/relu.c
    src/ml/activation/sigmoid.c
    src/ml/activation/sigmweight.c
    src/ml/activation/softplus.c
    src/ml/activation/softsign.c
)
add_library(miniai::miniai ALIAS miniai)

if(MINIAI_ENABLE_INVSQRT)
    target_sources(miniai PRIVATE src/ml/activation/invsqrt.c)
else()
    message(WARNING "InvSqrt is unfinished: source and tests excluded until Lab 2 A3.")
endif()

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

if(BUILD_TESTING)
    add_executable(miniai_activation_tests tests/activation_tests.c)
    target_link_libraries(miniai_activation_tests PRIVATE miniai::miniai)
    add_test(NAME miniai_activation_tests COMMAND miniai_activation_tests)
    set_tests_properties(miniai_activation_tests PROPERTIES TIMEOUT 15)
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
endif()


cmake_minimum_required(VERSION 3.16)
project(MiniAI VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_library(miniai
    src/ml/activation/activation.c
    src/ml/activation/elu.c
    src/ml/activation/gaussian.c
    src/ml/activation/leaky_relu.c
    src/ml/activation/relu.c
    src/ml/activation/sigmoid.c
    src/ml/activation/softplus.c
    src/ml/activation/softsign.c
)

add_library(miniai::miniai ALIAS miniai)

target_include_directories(miniai
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

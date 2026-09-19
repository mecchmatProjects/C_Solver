cmake_minimum_required(VERSION 3.20)
project(C_Solver C)

set(CMAKE_C_STANDARD 11)

add_executable(C_Solver main2.c Activation.c)
add_executable(C_Solver_khoroshun main2.c Activation.c task3_23.c)
add_executable(C_Solver_bykovska main2.c Activation.c task3_23.c t03_23.c)
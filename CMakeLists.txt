cmake_minimum_required(VERSION 3.20)
project(C_Solver C)

set(CMAKE_C_STANDARD 11)

add_executable(task_3_23_d lementa/task_3_23_d.c)

add_executable(C_Solver main2.c Activation.c)
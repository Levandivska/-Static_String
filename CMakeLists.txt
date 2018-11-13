cmake_minimum_required(VERSION 3.8)
project(untitled)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES  program2.c)
add_executable(untitled4 main.c my_lib.c my_lib.h)
add_executable(untitled41 program2.c my_lib.c my_lib.h)
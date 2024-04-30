cmake_minimum_required(VERSION 3.22)
project(os_unix_sparse_file C)

set(CMAKE_C_STANDARD 23)

add_executable(sparse src/main.c src/main.h)
add_executable(test src/test.c)
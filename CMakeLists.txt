cmake_minimum_required(VERSION 3.22)
project(os_unix_sparse_file C)

set(CMAKE_C_STANDARD 23)

add_executable(src/main.c src/main.h)
add_executable(src/test.c)
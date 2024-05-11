cmake_minimum_required(VERSION 3.20)

project(matrix_rain C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_EXTENSIONS)

# main executable
add_executable(rain "rain.c"  "randstr.c")
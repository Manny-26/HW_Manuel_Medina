cmake_minimum_required(VERSION 3.28)
project(Homework-01)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wcast-align -Wconversion -Wdouble-promotion -Wextra -Wnon-virtual-dtor -Wnull-dereference -Wold-style-cast -Woverloaded-virtual -Wpedantic -Wshadow -Wsign-conversion -Wunreachable-code)

add_compile_options(-fsanitize=address -fsanitize=leak -fsanitize=undefined)

add_link_options(-fsanitize=address -fsanitize=leak -fsanitize=undefined)

add_executable(Homework-01 src/main.cpp)

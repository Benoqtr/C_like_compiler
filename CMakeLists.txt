cmake_minimum_required(VERSION 3.10)

project(C_like_compiler)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(config)

add_subdirectory(lexical)

add_subdirectory(test)
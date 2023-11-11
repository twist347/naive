cmake_minimum_required(VERSION 3.26)
project(test_naive_array)

set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE SOURCES ./main.cpp)

add_executable(test_naive_array ${SOURCES})

target_link_libraries(test_naive_array gtest)
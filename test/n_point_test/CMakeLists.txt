cmake_minimum_required(VERSION 3.26)
project(test_naive_point)

set(CMAKE_CXX_STANDARD 23)

file(GLOB SOURCES ./main.cpp)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(test_naive_point ${SOURCES})

target_link_libraries(test_naive_point gtest)
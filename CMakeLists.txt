cmake_minimum_required(VERSION 3.27)
project(naive)

set(CMAKE_CXX_STANDARD 23)

add_executable(naive main.cpp)

target_include_directories(naive PRIVATE include)

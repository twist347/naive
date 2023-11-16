cmake_minimum_required(VERSION 3.26)

project(naive)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined,leak -fno-sanitize-recover=all")


add_subdirectory(test/n_array_test)
add_subdirectory(test/n_real_test)
add_subdirectory(test/n_vector_test)
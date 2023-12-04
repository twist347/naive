cmake_minimum_required(VERSION 3.26)

project(naive)

set(CMAKE_CXX_STANDARD 23)

if(CMAKE_BUILD_TYPE MATCHES "Debug")
    message("Debug build")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined,leak -fno-sanitize-recover=all")
endif()

add_subdirectory(test/n_array_test)
add_subdirectory(test/n_real_test)
add_subdirectory(test/n_vector_test)
add_subdirectory(test/n_sort_test)
add_subdirectory(test/n_search_test)
add_subdirectory(test/n_point_test)
add_subdirectory(test/n_unique_ptr_test)
add_subdirectory(test/n_shared_ptr)
add_subdirectory(test/n_stack_test)
add_subdirectory(test/n_string_test)
add_subdirectory(test/n_type_traits)
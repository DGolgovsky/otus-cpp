cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

set(BUILD_NUMBER 1)
project(ip_filter VERSION 0.0.$ENV{BUILD_NUMBER})

include(custom_cmake/functions.cmake)

add_subdirectory(libs/libfilter)
add_subdirectory(ip_filter-14)

if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests/libfilter)
endif()

include(custom_cmake/cpack.cmake)

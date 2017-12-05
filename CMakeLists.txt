cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(helloworld)

enable_testing()

include(cmake/functions.cmake)

add_subdirectory(libs/libhello)
add_subdirectory(helloapp)

if(BUILD_TESTING)
    add_subdirectory(tests/libhellotest)
endif()


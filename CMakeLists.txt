cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(allocator VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

include(custom_cmake/functions.cmake)

add_subdirectory(libs/cust_allocator)
add_subdirectory(libs/container)
add_subdirectory(app/allocator)

if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests/catch-test)
endif()

include(custom_cmake/cpack.cmake)

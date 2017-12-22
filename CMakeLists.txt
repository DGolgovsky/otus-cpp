cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(allocator VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

include(custom_cmake/functions.cmake)

add_subdirectory(libs/liballocator)
add_subdirectory(app/allocator)

if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests/liballocator)
endif()

include(custom_cmake/cpack.cmake)

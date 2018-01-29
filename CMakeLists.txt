cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

if(DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(print_ip VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(print_ip VERSION 0.0.1)
endif()

include(custom_cmake/functions.cmake)

add_subdirectory(libs/libprinter)
add_subdirectory(app/print_ip)

if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests/catch-test)
endif()

include(custom_cmake/cpack.cmake)

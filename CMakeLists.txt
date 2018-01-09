cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

if(DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(ip_filter VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(ip_filter VERSION 0.0.1)
endif()

include(custom_cmake/functions.cmake)

add_subdirectory(libs/libfilter)
add_subdirectory(app/ip_filter)

if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests/catch-test)
endif()

include(custom_cmake/cpack.cmake)

cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(helloworld VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

enable_testing()

include(cmake_customs/functions.cmake)

add_subdirectory(libs/libhello)
add_subdirectory(helloapp)

if(BUILD_TESTING)
    #add_subdirectory(tests/libhellotest)
    add_subdirectory(tests/version_boost_test)
endif()

include(cmake_customs/cpack.cmake)

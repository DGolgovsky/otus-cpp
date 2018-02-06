cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

if(DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(editor VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(editor VERSION 0.0.1)
endif()

include(custom_cmake/functions.cmake)

add_subdirectory(libs/libeditor)
add_subdirectory(app/editor)

if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests/catch-test)
endif()

include(custom_cmake/cpack.cmake)

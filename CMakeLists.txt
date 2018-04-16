cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

set(TARGET bulkmt)

if(DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(${TARGET} VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(${TARGET} VERSION 0.0.1)
endif()

file(GLOB TARGET_SRC
        "${CMAKE_CURRENT_SOURCE_DIR}/sources/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/sources/*.h")
add_executable(${TARGET} ${TARGET_SRC})

set_target_properties(${TARGET} PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON)
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set_target_properties(${TARGET} PROPERTIES COMPILE_FLAGS "-stdlib=libc++ -pthread")
endif()
target_compile_options(${TARGET} PRIVATE -Wall -Wextra -Wpedantic)
if (CMAKE_COMPILER_IS_GNUCC)
    option(ENABLE_COVERAGE "Enable coverage reporting for gcc/clang"
            FALSE)
    if (ENABLE_COVERAGE)
        target_compile_options(${TARGET} --coverage -O2)
    endif()
endif()

find_package(Threads)

target_link_libraries(${TARGET} ${CMAKE_THREAD_LIBS_INIT})

install(TARGETS ${TARGET} RUNTIME DESTINATION bin)

if(BUILD_TESTING)
    enable_testing()
    file(GLOB TARGET_SRC
            "${CMAKE_CURRENT_SOURCE_DIR}/tests/catch-test/*.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/tests/catch-test/*.h")
    add_executable(catch-test ${TARGET_SRC})
    target_include_directories(catch-test PRIVATE
            "${CMAKE_SOURCE_DIR}/tests/catch")

    add_test(catch-test)
endif()

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_PACKAGE_VERSION_BUILD ${TRAVIS_BUILD_NUMBER})
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE amd64)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Bulk MT")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Dmitry Golgovsky")
set(CPACK_PACKAGE_CONTACT d.westcoast@aol.com)

include(CPack)

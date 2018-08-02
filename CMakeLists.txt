cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

set(TARGET bulk_server)
set(BASE async)
set(BASE_MT bulkmt)

if(DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(${TARGET} VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(${TARGET} VERSION 0.0.1)
endif()

find_package(Threads)
find_package(Boost COMPONENTS system REQUIRED)

file(GLOB BASE_MT_SRC
        "${CMAKE_CURRENT_SOURCE_DIR}/async/bulkmt/sources/*.cpp")

add_library(${BASE_MT} SHARED ${BASE_MT_SRC})
target_link_libraries(${BASE_MT} ${CMAKE_THREAD_LIBS_INIT})

file(GLOB BASE_SRC
        "${CMAKE_CURRENT_SOURCE_DIR}/async/sources/*.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/async/sources/*.h")

add_library(${BASE} SHARED ${BASE_SRC})
target_link_libraries(${BASE} ${BASE_MT})
target_include_directories(${BASE} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/async/bulkmt/sources/")

file(GLOB TARGET_SRC
        "${CMAKE_CURRENT_SOURCE_DIR}/sources/*.cpp")
add_executable(${TARGET} ${TARGET_SRC})

include_directories(${Boost_INCLUDE_DIR})
target_link_libraries(${TARGET} ${BASE} ${Boost_LIBRARIES})
target_include_directories(${TARGET} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/async/sources/")

set_target_properties(${TARGET} ${BASE} ${BASE_MT} PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON)
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set_target_properties(${BASE_MT} ${BASE} ${TARGET} PROPERTIES COMPILE_FLAGS "-stdlib=libc++ -pthread")
endif()

target_compile_options(${TARGET} PRIVATE -Wall -Wextra -Wpedantic)
target_compile_options(${BASE} PRIVATE -Wall -Wextra -Wpedantic)
target_compile_options(${BASE_MT} PRIVATE -Wall -Wextra -Wpedantic)

if (CMAKE_COMPILER_IS_GNUCC)
    option(ENABLE_COVERAGE "Enable coverage reporting for gcc/clang"
            FALSE)
    if (ENABLE_COVERAGE)
        add_compile_options(--coverage -O0)
    endif()
endif()

install(TARGETS ${TARGET}
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib)

if(BUILD_TESTING)
    add_executable(bulk_server main.cpp)
    target_link_libraries(${TARGET} ${CMAKE_THREAD_LIBS_INIT})

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
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE amd64)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Bulk server")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Dmitry Golgovsky")
set(CPACK_PACKAGE_CONTACT d.westcoast@aol.com)

include(CPack)

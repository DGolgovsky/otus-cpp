cmake_minimum_required(VERSION 3.2)

if (CMAKE_COMPILER_IS_GNUCC)
  option(ENABLE_COVERAGE "Enable coverage reporting for gcc/clang" FALSE)

  if (ENABLE_COVERAGE)
    add_compile_options(--coverage -O0)
  endif()
endif()

project(helloworld VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file(in.version.h version.h)

add_executable(helloworld_cli main.cpp)

add_executable(test_version_cli test.cpp)

set_target_properties(helloworld_cli test_version_cli PROPERTIES
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED ON
	COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)

set_target_properties(test_version_cli PROPERTIES
	COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
	INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(helloworld_cli
	pthread
	--coverage
)

target_link_libraries(test_version_cli
	pthread
	${Boost_LIBRARIES}
	--coverage
)

install(TARGETS helloworld_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT d.westcoast@aol.com)

include(CPack)

enable_testing()

add_test(test_version test_version_cli)

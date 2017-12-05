configure_file("${CMAKE_SOURCE_DIR}/libs/version/in.version.h" "${CMAKE_SOURCE_DIR}/libs/version/version.h")
custom_add_boost_test(version_boost_test)

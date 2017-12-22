custom_add_library(liballocator)

custom_compiler_opts(liballocator)

target_include_directories(liballocator INTERFACE
                           ${CMAKE_CURRENT_SOURCE_DIR}/..)


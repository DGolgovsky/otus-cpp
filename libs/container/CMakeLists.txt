custom_add_library(container)

custom_compiler_opts(container)

target_include_directories(container INTERFACE
                           ${CMAKE_CURRENT_SOURCE_DIR}/..)


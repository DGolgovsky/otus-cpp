custom_add_library(libfilter)

custom_compiler_opts(libfilter)

target_include_directories(libfilter INTERFACE
                           ${CMAKE_CURRENT_SOURCE_DIR}/..)


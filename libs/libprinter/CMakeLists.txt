custom_add_library(libprinter)

custom_compiler_opts(libprinter)

target_include_directories(libprinter INTERFACE
                           ${CMAKE_CURRENT_SOURCE_DIR}/..)


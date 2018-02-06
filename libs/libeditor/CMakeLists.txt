custom_add_library(libeditor)

custom_compiler_opts(libeditor)

target_include_directories(libeditor INTERFACE
                           ${CMAKE_CURRENT_SOURCE_DIR}/..)


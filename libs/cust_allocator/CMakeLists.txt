custom_add_library(cust_allocator)

custom_compiler_opts(cust_allocator)

target_include_directories(cust_allocator INTERFACE
                           ${CMAKE_CURRENT_SOURCE_DIR}/..)


custom_add_executable(print_ip)

custom_compiler_opts(print_ip)

target_link_libraries(print_ip libprinter)

install(TARGETS print_ip RUNTIME DESTINATION bin)

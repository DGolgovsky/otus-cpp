custom_add_executable(ip_print)

custom_compiler_opts(ip_print)

#target_link_libraries(ip_print libfilter)

install(TARGETS ip_print RUNTIME DESTINATION bin)

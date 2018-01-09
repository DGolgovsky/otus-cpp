custom_add_executable(ip_filter)

custom_compiler_opts(ip_filter)

target_link_libraries(ip_filter libfilter)

install(TARGETS ip_filter RUNTIME DESTINATION bin)

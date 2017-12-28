custom_add_executable(allocator)

custom_compiler_opts(allocator)

target_link_libraries(allocator cust_allocator container)

install(TARGETS allocator RUNTIME DESTINATION bin)

custom_add_executable(editor)

custom_compiler_opts(editor)

target_link_libraries(editor libeditor)

install(TARGETS editor RUNTIME DESTINATION bin)

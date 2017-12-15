install(TARGETS ${CMAKE_CURRENT_BINARY_DIR}/app/ip_filter-14/ip_filter-14 RUNTIME DESTINATION bin)

if (BINARY_PACKAGING_MODE)
	execute_process(COMMAND "${CMAKE_COMMAND}" -E create_symlink
                    ip_filter-14
                    ${CMAKE_CURRENT_BINARY_DIR}/ip_filter)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/ip_filter
            RUNTIME DESTINATION bin)
endif ()

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT d.westcoast@aol.com)

include(CPack)


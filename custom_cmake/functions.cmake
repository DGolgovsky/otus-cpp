function(custom_compiler_opts TARGET)
	target_compile_features(${TARGET}
	    PUBLIC
			cxx_std_14
			cxx_variadic_templates
			cxx_nullptr
		PRIVATE
			cxx_lambdas
	)
	set_target_properties(${TARGET} PROPERTIES
	    CXX_STANDARD 14
	    CXX_STANDARD_REQUIRED ON
	)
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set_target_properties(${TARGET} PROPERTIES COMPILE_FLAGS "-stdlib=libc++ -pthread")
        target_link_libraries(${TARGET} pthread)
    endif()
    target_compile_options(${TARGET} PRIVATE -Wall -Wextra -Wpedantic)
    if (CMAKE_COMPILER_IS_GNUCC)
        option(ENABLE_COVERAGE "Enable coverage reporting for gcc/clang"
               FALSE)
        if (ENABLE_COVERAGE)
            target_compile_options(${TARGET} --coverage -O2)
        endif()
    endif()
endfunction()

function(custom_add_library TARGET)
    file(GLOB TARGET_SRC
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
    add_library(${TARGET} ${TARGET_SRC})
endfunction()

function(custom_add_executable TARGET)
    file(GLOB TARGET_SRC
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
    add_executable(${TARGET} ${TARGET_SRC})
endfunction()

function(custom_add_tests TARGET LIBRARY)
    custom_add_executable(${TARGET})
    target_include_directories(${TARGET} PRIVATE
                              "${CMAKE_SOURCE_DIR}/libs/catch")
    target_link_libraries(${TARGET} ${LIBRARY})
    add_test(${TARGET} ${TARGET})
endfunction()

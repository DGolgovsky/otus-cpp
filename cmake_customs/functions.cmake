function(custom_enable_coverage TARGET)
    # Compiler coverage
    if (CMAKE_COMPILER_IS_GNUCC)
        option(ENABLE_COVERAGE "Enable coverage reporting for gcc/clang" FALSE)
        
        if (ENABLE_COVERAGE)
            add_compile_options(--coverage -O0)
        endif()
    endif()
endfunction(custom_enable_coverage)

function(custom_enable_warnings TARGET)
    # Warnings
    if (MSVC)
        add_compile_options(/W4)
    else()
        add_compile_options(-Wall -Wextra -Wpedantic)
    endif()
endfunction(custom_enable_warnings)

function(custom_enable_cxx14 TARGET)
    target_compile_features(${TARGET} PUBLIC cxx_std_14)
    set_target_properties(${TARGET} PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
    )
    target_compile_features(${TARGET} PRIVATE cxx_lambda_init_captures)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        set_target_properties(${TARGET} PROPERTIES COMPILE_FLAGS "/std:c++latest")
    elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set_target_properties(${TARGET} PROPERTIES COMPILE_FLAGS "-stdlib=libc++ -pthread")
        target_link_libraries(${TARGET} c++14 pthread)
    endif()
endfunction(custom_enable_cxx14)

function(custom_add_library_from_dir TARGET)
    file(GLOB TARGET_SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
    add_library(${TARGET} ${TARGET_SRC})
endfunction()

function(custom_add_executable_from_dir TARGET)
    file(GLOB TARGET_SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
    add_executable(${TARGET} ${TARGET_SRC})
endfunction()

function(custom_add_test_from_dir TARGET LIBRARY)
    custom_add_executable_from_dir(${TARGET})
    target_include_directories(${TARGET} PRIVATE "${CMAKE_SOURCE_DIR}/libs/catch")
    target_link_libraries(${TARGET} ${LIBRARY})
    add_test(${TARGET} ${TARGET})
endfunction()

function(custom_add_boost_test TARGET)
    set(Boost_USE_STATIC_LIBS OFF)
    set(Boost_USE_MULTITHREADED ON)
    set(Boost_USE_STATIC_RUNTIME OFF)
    #find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
	find_package(Boost COMPONENTS unit_test_framework REQUIRED)
    
	if(Boost_FOUND)
		include_directories(${Boost_INCLUDE_DIRS})
		custom_add_executable_from_dir(${TARGET})
		target_include_directories(${TARGET} PRIVATE "${CMAKE_SOURCE_DIR}/libs/version")
        target_link_libraries(${TARGET} pthread ${Boost_LIBRARIES} --coverage)
		set_target_properties(${TARGET} PROPERTIES COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK)
        add_test(${TARGET} ${TARGET})
    else()
        message(SEND_ERROR "Failed to find boost::unit_test_framework")
        return()
    endif()
endfunction()


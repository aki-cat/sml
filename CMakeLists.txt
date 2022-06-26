cmake_minimum_required(VERSION 3.10)
project(sml VERSION 0.2.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# LIBRARY INCLUDE

add_library(sml INTERFACE)
target_include_directories(sml INTERFACE .)

# TESTS

if(SML_RUN_TESTS)
    if (MSVC)
        add_compile_options(/W3 /WX /Od)
    else(MSVC)
        add_compile_options(-Wall -pedantic -Werror -O0 -Wextra)
    endif(MSVC)

    add_executable(sml_tests "${PROJECT_SOURCE_DIR}/tests/tests.cc")

    add_subdirectory("${PROJECT_SOURCE_DIR}/third_party/btl")
    target_link_libraries(sml_tests btl)

    target_include_directories(sml_tests PRIVATE "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}")
    set_target_properties(sml_tests
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    )

    if(MSVC)
        add_custom_command(
            TARGET sml_tests
            DEPENDS sml_tests
            COMMAND ${CMAKE_BINARY_DIR}/Debug/sml_tests.exe
        )
    else(MSVC)
        add_custom_command(
            TARGET sml_tests
            DEPENDS sml_tests
            COMMAND "${CMAKE_BINARY_DIR}/sml_tests"
        )
    endif(MSVC)
endif(SML_RUN_TESTS)

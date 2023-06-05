project(Google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


add_executable(Google_Tests_run
        lexer_tests.cpp
        sasm_tests.cpp
        stack_vm_tests.cpp
        )

target_link_libraries(
        Google_Tests_run
        gtest
        gtest_main
        sasm_lib
        stack_vm_lib
)
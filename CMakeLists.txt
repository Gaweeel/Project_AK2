cmake_minimum_required(VERSION 3.24)
project(Project_AK2)
set(CMAKE_CXX_STANDARD 23)
include_directories(src)

add_executable(
        sasm
        src/sasm/lexer.cpp
        src/sasm/lexer.h
        src/sasm/sasm.cpp
)
add_executable(
        stack_vm
        src/stack_vm/stack_vm.cpp
        src/stack_vm/stack_vm.h
        src/stack_vm/main.cpp
)
add_subdirectory(Google_tests)
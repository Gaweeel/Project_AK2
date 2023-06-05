cmake_minimum_required(VERSION 3.24)
project(Project_AK2)
add_library(
        stack_vm_lib STATIC
        main.cpp
        stack_vm.cpp
        stack_vm.h
        )
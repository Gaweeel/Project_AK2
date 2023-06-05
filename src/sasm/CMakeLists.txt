cmake_minimum_required(VERSION 3.24)
project(Project_AK2)
add_library(
        sasm_lib STATIC
        lexer.cpp
        sasm.cpp
        lexer.h
        )

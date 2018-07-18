cmake_minimum_required(VERSION 3.10)
project(ascii_obfuscation C)

set(CMAKE_C_STANDARD 11)

include_directories(sources)

add_executable(ascii_obfuscation
        sources/deprecated_functions.c
        sources/deprecated_functions.h
        sources/main.c)

cmake_minimum_required(VERSION 3.10)
project(ascii_obfuscation C)

set(CMAKE_C_STANDARD 11)

include_directories(sources
                    sources/Unity/src)

file( GLOB_RECURSE source_files
      sources/deprecated_functions.c
      sources/deprecated_functions.h
      sources/functions.c
      sources/utils.c)
file( GLOB_RECURSE test_files "sources/Unity/src/*.c" )

add_executable( ascii_obfuscation
                ${source_files}
                sources/main.c)

add_executable( unit_tests
                ${source_files}
                ${test_files}
                sources/unit_tests.c)

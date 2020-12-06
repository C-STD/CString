cmake_minimum_required(VERSION 3.0)
project(CString)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories("./")

add_library(CString STATIC cstring/cstring.c)

if(BUILD_TESTS)
    add_subdirectory(tests/)
endif(BUILD_TESTS)

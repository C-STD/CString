cmake_minimum_required(VERSION 3.0)
project(CString)

include_directories("./")

if(BUILD_TESTS)
    add_subdirectory(tests/)
endif(BUILD_TESTS)

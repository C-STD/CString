
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/tests)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/tests)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/tests)

set(TESTS_FILE
    cstring_at_test.c
    cstring_back_test.c
    cstring_begin_test.c
    cstring_capacity_test.c
    cstring_clear_test.c
    cstring_create_test.c
    cstring_data_test.c
    cstring_destroy_test.c
    cstring_empty_test.c
    cstring_end_test.c
    cstring_equal_test.c
    cstring_erase_test.c
    cstring_front_test.c
    cstring_insert_test.c
    cstring_length_test.c
    cstring_maxsize_test.c
    cstring_pushback_test.c
    cstring_rbegin_test.c
    cstring_rend_test.c
    cstring_reserve_test.c
    cstring_shrinktofit_test.c
    cstring_size_test.c
    cstring_replace_test.c
    cstring_substr_test.c
    cstring_copy_test.c
)

foreach(CSTRING_TEST_FILE ${TESTS_FILE})
    string(REPLACE ".c" "" CSTRING_TEST_FILE_NAME ${CSTRING_TEST_FILE})
    add_executable(${CSTRING_TEST_FILE_NAME} ${CSTRING_TEST_FILE})
    target_link_libraries(${CSTRING_TEST_FILE_NAME} CString)
endforeach(CSTRING_TEST_FILE ${CSTRING_TESTS})
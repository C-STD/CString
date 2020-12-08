#ifndef TEST_UNIT_H
#define TEST_UNIT_H

#include <assert.h>

#define ASSERT(expr) assert(expr)

#define ASSERT_EQ(value, expected_value) ASSERT(value == expected_value)

#define ASSERT_NEQ(value, expected_value) ASSERT(value != expected_value)

#define TEST(test_name) void test_name()

#define RUN_TEST(test_name) test_name()

#endif
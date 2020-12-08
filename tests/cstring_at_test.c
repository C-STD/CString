#include "cstring/cstring.h"
#include "test_unit.h"
#include <string.h>

TEST(CStringAtValueTest)
{
	void* my_string = CStringCreate();

	ASSERT_NEQ(my_string, NULL);

	const char* test_string = "Hello, World!\0";
	size_t test_string_len = strlen(test_string);

	ASSERT_EQ(CStringEqual(my_string, test_string), strlen(test_string) + 1);

	for(size_t i = 0; i < test_string_len; i++)
	{
		ASSERT_EQ(*CStringAt(my_string, i), test_string[i]);
	}

	CStringDestroy(my_string);
}

TEST(CStringAtChangedValueTest)
{
	void* my_string = CStringCreate();

	ASSERT_NEQ(my_string, NULL);

	const char* test_string = "Hello, World!\0";
	size_t test_string_len = strlen(test_string);

	ASSERT_EQ(CStringEqual(my_string, test_string), strlen(test_string) + 1);

	for(size_t i = 0; i < test_string_len; i++)
	{
		*CStringAt(my_string, i) = 'A';
		ASSERT_EQ(*CStringAt(my_string, i), 'A');
	}

	CStringDestroy(my_string);
}

TEST(CStringAtInvalidIndexTest)
{
	void* my_string = CStringCreate();

	ASSERT_NEQ(my_string, NULL);

	const char* test_string = "Hello, World!\0";
	size_t test_string_len = strlen(test_string);

	ASSERT_EQ(CStringEqual(my_string, test_string), strlen(test_string) + 1);

	ASSERT_EQ(CStringAt(my_string, 100), NULL);
	ASSERT_EQ(CStringAt(my_string, -1), NULL);

	CStringDestroy(my_string);	
}

int main()
{
	RUN_TEST(CStringAtValueTest);
	RUN_TEST(CStringAtChangedValueTest);
	RUN_TEST(CStringAtInvalidIndexTest);
	return 0;
}

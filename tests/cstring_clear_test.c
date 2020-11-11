#include "cstring/cstring.h"
#include <assert.h>
#include <string.h>
int main()
{
	void* my_string = CStringCreate();

	assert(CStringEqual(my_string, "HELLO\0") == 6);

	CStringClear(my_string);
	
	assert(CStringSize(my_string) == (size_t)0);
	assert(CStringLength(my_string) == (size_t)0);

	CStringDestroy(my_string);
	return 0;
}

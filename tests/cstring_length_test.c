#include "cstring/cstring.h"
#include <assert.h>
#include <string.h>
int main()
{
	void* my_string = CStringCreate();
	assert(my_string != NULL);
	assert(CStringLength(my_string) == 0);
	assert(CStringEqual(my_string, "Hello, World!\0") == 0);
	assert(CStringLength(my_string) == 13);

	CStringDestroy(my_string);

	return 0;
}

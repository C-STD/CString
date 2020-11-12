#include "cstring/cstring.h"
#include <assert.h>
#include <string.h>
int main()
{
	void* my_string = CStringCreate();

	assert(CStringEqual(my_string, "HELLO\0") == 6);
	assert(strcmp(CStringData(my_string), "HELLO\0") == 0);
	assert(CStringEqual(my_string, "LONGER TEST STRING\0") == 19);
	assert(strcmp(CStringData(my_string), "LONGER TEST STRING\0") == 0);
	
	CStringDestroy(my_string);

	return 0;
}

#include "cstring/cstring.h"
#include <assert.h>
#include <string.h>
int main()
{
	void* my_string = CStringCreate();

	assert(CStringEmpty(my_string) == 0);
	assert(CStringEqual(my_string, "HELLO\0") == 6);
	assert(CStringEmpty(my_string) != 0);

	CStringDestroy(my_string);
	return 0;
}

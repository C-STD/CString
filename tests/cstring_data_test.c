#include "cstring/cstring.h"
#include <assert.h>
#include <string.h>
int main()
{
	void* my_string = CStringCreate();

	assert(CStringEqual(my_string, "HELLO\0") == 6);

	assert(CStringData(my_string) != NULL);
	assert(strcmp("HELLO", CStringData(my_string)) == 0);

	CStringDestroy(my_string);

	return 0;
}

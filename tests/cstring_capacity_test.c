#include "cstring/cstring.h"
#include <assert.h>
#include <string.h>
int main()
{
	void* my_string = CStringCreate();

	assert(CStringEqual(my_string, "HELLO\0") == 6);

	assert(CStringCapacity(my_string) == (size_t)(9));

	CStringDestroy(my_string);

	return 0;
}

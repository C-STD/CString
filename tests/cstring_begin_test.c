#include "cstring/cstring.h"
#include <assert.h>
#include <string.h>
int main()
{
	void* my_string = CStringCreate();

	assert(CStringEqual(my_string, "HELLO\0") == 6);

	assert(*(char*)(CStringBegin(my_string)) == 'H');

	CStringDestroy(my_string);

	return 0;
}

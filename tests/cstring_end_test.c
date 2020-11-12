#include "cstring/cstring.h"
#include <assert.h>
#include <string.h>
int main()
{
	void* my_string = CStringCreate();

	assert(CStringEnd(my_string) == NULL);
	assert(CStringEqual(my_string, "HELLO\0") == 6);
	assert(*((char*)CStringEnd(my_string)) == '\0');

	CStringDestroy(my_string);

	return 0;
}

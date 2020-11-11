#include "cstring/cstring.h"
#include <assert.h>
#include <string.h>
int main()
{
	void* my_string = CStringCreate();

	assert(CStringEqual(my_string, "HELLO\0") == 6);

	assert(*CStringBack(my_string) == 'O');

	CStringDestroy(my_string);

	return 0;
}

#include "cstring/cstring.h"
#include <assert.h>
#include <string.h>
int main()
{
	void* my_string = CStringCreate();

	assert(CStringEqual(my_string, "HELLO\0") == 6);

	assert(*CStringAt(my_string, 0) == 'H');
	assert(*CStringAt(my_string, 1) == 'E');
	assert(*CStringAt(my_string, 2) == 'L');
	assert(*CStringAt(my_string, 3) == 'L');
	assert(*CStringAt(my_string, 4) == 'O');
	assert(CStringAt(my_string, 52) == NULL);

	CStringDestroy(my_string);

	return 0;
}

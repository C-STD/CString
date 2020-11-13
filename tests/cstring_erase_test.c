#include "cstring/cstring.h"
#include <assert.h>
#include <string.h>
int main()
{
	void* my_string = CStringCreate();

	assert(my_string != NULL);

	assert(CStringEqual(my_string, "HELLO\0") == 6);
	assert(CStringErase(my_string, 4) == 0);
	assert(strcmp(CStringData(my_string), "HELL\0") == 0);

	assert(CStringErase(my_string, 0) == 0);
	assert(strcmp(CStringData(my_string), "ELL\0") == 0);

	return 0;
}

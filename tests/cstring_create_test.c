#include "cstring/cstring.h"
#include <assert.h>
#include <string.h>
int main()
{
	void* my_string = CStringCreate();
	assert(my_string != NULL);
	CStringDestroy(my_string);

	return 0;
}

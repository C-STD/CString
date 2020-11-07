#include "cstring/cstring.h"
#include <assert.h>
#include <string.h>
int main()
{
	void* my_string = CStringCreate();
	assert(CStringDestroy(my_string) == 0);

	return 0;
}

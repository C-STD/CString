#include "cstring/cstring.h"
#include <assert.h>
#include <string.h>
int main()
{
	void* my_string = CStringCreate();
    void* my_copy_string = CStringCreate();

	assert(CStringEqual(my_string, "HELLO\0") == 6);
    assert(CStringCopy(my_copy_string, my_string) == 6);

    assert(strcmp(CStringData(my_string), CStringData(my_copy_string)) == 0);

	CStringDestroy(my_string);
    CStringDestroy(my_copy_string);
	return 0;
}

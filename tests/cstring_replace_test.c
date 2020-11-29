#include "cstring/cstring.h"
#include <assert.h>
#include <string.h>
int main()
{
	void* my_string = CStringCreate();

	assert(CStringEqual(my_string, "DSLLO") == 6);
    assert(CStringReplace(my_string, "H", 0, 1) == 1);

    assert(CStringReplace(my_string, "HE", 0, 2) == 2);
    assert(CStringReplace(my_string, "WORLD", 0, 5) == 5);

    assert(CStringReplace(my_string, "HELLO_WORLD", 0, 4000) == 0);
    assert(CStringReplace(my_string, "HELLO_WORLD", 50, 11) == 0);
    assert(CStringReplace(my_string, NULL, 10, 10) == 0);
    assert(CStringReplace(my_string, "Hello", 0, 0) == 0);

	CStringDestroy(my_string);
	return 0;
}

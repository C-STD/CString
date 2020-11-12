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

	// This test will always fail because at the moment, `CStringErase` just
	// replace the character at the given index with a NULL character(\0).
	// So, basically the result in this test case would be that the string is now
	// `empty`, or in simpler terms the CString is now equal to "\0ELL" and
	// because `strcmp` reads until it finds a `\0`, the two strings are treated as
	// different.
	// TODO: Fix `CStringErase` to allow erasing at the start/middle of the CString.
	assert(CStringErase(my_string, 0) == 0);
	assert(strcmp(CStringData(my_string), "ELL\0") == 0);

	return 0;
}

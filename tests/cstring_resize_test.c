#include "cstring/cstring.h"
#include <assert.h>
#include <string.h>
int main()
{
    void* str0 = CStringCreate();
    void* str1 = CStringCreate();

    assert(CStringEqual(str0, "HELLO\0") == 6);
    assert(CStringEqual(str1, "WORLD\0") == 6);

    assert(CStringResize(str0, 10, 0) == 0);
    assert(CStringResize(str1, 3, 0) == 0);
    assert(CStringResize(NULL, 0, 0) == 1);

    CStringDestroy(str0);
    CStringDestroy(str1);
	return 0;
}
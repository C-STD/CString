#include "cstring/cstring.h"
#include <assert.h>
#include <string.h>
int main()
{
    void* my_string = CStringCreate();

    assert(CStringEqual(my_string, "Hello, World!\0") == 14);

    void* hello = CStringSubStr(my_string, 0, 5);
    void* world = CStringSubStr(my_string, 7, 13);
    
    assert(hello != NULL);
    assert(world != NULL);
    
    assert(CStringData(hello) != NULL);
    assert(CStringData(world) != NULL);

    assert(strcmp(CStringData(hello), "Hello\0") == 0);
    assert(strcmp(CStringData(world), "World!\0") == 0);

    hello = CStringSubStr(my_string, 0, 0);
    assert(strcmp(CStringData(hello), "Hello, World!\0") == 0);

    CStringClear(hello);

    hello = CStringSubStr(my_string, 13, 7);
    assert(strcmp(CStringData(hello), "World!\0") == 0);

    CStringDestroy(my_string);
    CStringDestroy(hello);
    CStringDestroy(world);
	return 0;
}

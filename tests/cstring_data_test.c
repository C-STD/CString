#include "cstring/cstring.h"
#include <assert.h>
#include <string.h>

int main()
{
    void* mystr = CStringCreate();
    assert(mystr != NULL);

    size_t size = CStringSize(mystr);
    assert(size == 0);

    size_t length = CStringLength(mystr);
    assert(length == 0);
    
    size_t capacity = CStringCapacity(mystr);
    assert(capacity == 0);

    assert(CStringEqual(mystr, "Hello, World!\0") == 14);

    assert(CStringData(mystr) != NULL);
    assert(strcmp(CStringData(mystr), "Hello, World!\0") == 0);
    // printf("DATA: %s", CStringData(mystr));

    size = CStringSize(mystr);
    assert(size == 14);

    length = CStringLength(mystr);
    assert(length == 14);
    
    capacity = CStringCapacity(mystr);
    assert(capacity == 21);

    assert(CStringDestroy(mystr) == 0);
}
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

    // This test fails.
    // Reason: We're not updating `CString::begin` and `CString::end`.
    // TODO: Update `CString::begin` and `CString::end` in `CStringEqual` function.
    assert(CStringFront(mystr) != NULL);
    assert(CStringBack(mystr) != NULL);
    assert(CStringMaxSize() == 0);

    assert(CStringDestroy(mystr) == 0);
}
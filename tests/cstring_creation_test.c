#include "cstring/cstring.h"
#include <assert.h>

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

    assert(CStringBegin(mystr) == NULL);
    assert(CStringEnd(mystr) == NULL);

    assert(CStringDestroy(mystr) == 0);
}
#include "cstring.h"
#include <stdlib.h>
#include <memory.h>
#include <string.h>

typedef struct __denx__cstring_object
{
    char* string;

    size_t length;

    size_t size;

    size_t capacity;

    void* begin;

    void* end;

}denx_cstring;

#define CSTRING_REF(ptr) ((denx_cstring*)(ptr))

void CStringStaticIncreaseCapacity(void*);

void* CStringCreate()
{
    denx_cstring* string = (denx_cstring*)(malloc(sizeof(denx_cstring)));
    string->string = NULL;
    string->length = 0;
    string->size = 0;
    string->capacity = 0;
    string->begin = NULL;
    string->end = NULL;
    return (void*)string;
}

size_t CStringDestroy(void* ptr)
{
    if(ptr != NULL)
    {
        if(((denx_cstring*)(ptr))->string != NULL)
        {
            free(((denx_cstring*)(ptr))->string);
        }
        free(ptr);
        return 0;
    }
    return 1;
}

// Calculates the length of the CString and returns it.
size_t CStringLength(void* ptr)
{
    if(ptr != NULL)
    {
        size_t i = 0;
        if(((denx_cstring*)(ptr))->size == 0)
        {
            return i;
        }
        
        for(;;)
        {
            if(((denx_cstring*)(ptr))->string[i++] == '\0')
            {
                break;  
            }
        }
        return i;
    }
    return 0;
}

size_t CStringSize(void* ptr)
{
    return ((denx_cstring*)(ptr))->size;
}

size_t CStringCapacity(void* ptr)
{
    return ((denx_cstring*)(ptr))->capacity;
}

char* CStringAt(void* ptr, size_t index)
{
    if(ptr != NULL && index < ((denx_cstring*)(ptr))->size)
    {
        return &((denx_cstring*)(ptr))->string[index];
    }
    return NULL;
}

void CStringClear(void* ptr)
{
    if(ptr != NULL)
    {
        memset(((denx_cstring*)(ptr))->string, 0, ((denx_cstring*)(ptr))->size);
    }
}

void* CStringBegin(void* ptr)
{
    if(ptr != NULL)
    {
        return ((denx_cstring*)(ptr))->begin;
    }
    return NULL;
}

void* CStringEnd(void* ptr)
{
    if(ptr != NULL)
    {
        return ((denx_cstring*)(ptr))->end;
    }
    return NULL;
}

void* CStringRBegin(void* ptr)
{
    return CStringEnd(ptr);
}

void* CStringREnd(void* ptr)
{
    return CStringBegin(ptr);
}

size_t CStringEqual(void* ptr, const char* str)
{
    if(ptr != NULL && str != NULL)
    {
        size_t str_len = strlen(str);

        if(((denx_cstring*)(ptr))->string == NULL)
        {
            ((denx_cstring*)(ptr))->string = (char*)malloc(str_len);
            memset(((denx_cstring*)(ptr))->string, 0, str_len);

            ((denx_cstring*)(ptr))->begin = (void*)((denx_cstring*)(ptr))->string;
            ((denx_cstring*)(ptr))->end = (void*)((denx_cstring*)(ptr))->string + str_len;
        }

        strcpy_s(((denx_cstring*)(ptr))->string, str_len + 1, str);
        ((denx_cstring*)(ptr))->length = strlen(((denx_cstring*)(ptr))->string);

        if(((denx_cstring*)(ptr))->length > ((denx_cstring*)(ptr))->size)
        {
            ((denx_cstring*)(ptr))->size = ((denx_cstring*)(ptr))->length + 1;
            CStringStaticIncreaseCapacity(ptr); // Increase the capacity of the string.
        }

        if(!strcmp(((denx_cstring*)(ptr))->string, str))
        {
            return ((denx_cstring*)(ptr))->size; 
        }
    }
    return 0;
}

const char* CStringData(void* ptr)
{
    if(ptr != NULL)
    {
        return ((denx_cstring*)(ptr))->string;
    }
    return NULL;
}

void CStringStaticIncreaseCapacity(void* ptr)
{
    if(ptr != NULL)
    {
        size_t ssize = ((denx_cstring*)(ptr))->size;

        char* temp_str = (char*)malloc(ssize);
        
        size_t ncapacity = ssize + (ssize / 2);

        strcpy_s(temp_str, ssize, ((denx_cstring*)(ptr))->string);

        free(((denx_cstring*)(ptr))->string);
        ((denx_cstring*)(ptr))->string = NULL;

        ((denx_cstring*)(ptr))->string = (char*)malloc(ssize + (ssize / 2));
        strcpy_s(((denx_cstring*)(ptr))->string, ssize, temp_str);
        ((denx_cstring*)(ptr))->capacity = ncapacity;

        free(temp_str);
        temp_str = NULL;
    }
}

size_t CStringEmpty(void* ptr)
{
    if(ptr != NULL)
    {
        return ((denx_cstring*)(ptr))->length;
    }
    return 1;
}

// Returns a pointer to the first character of the CString or NULL.
char* CStringFront(void* ptr)
{
    if(ptr != NULL)
    {
        if(((denx_cstring*)(ptr))->string != NULL && ((denx_cstring*)(ptr))->size > 0)
        {
            return (char*)CStringBegin(ptr);
        }
    }
    return NULL;
}

// Returns a pointer to the last character of the CString or NULL.
char* CStringBack(void* ptr)
{
    if(ptr != NULL)
    {
        if(((denx_cstring*)(ptr))->string != NULL && ((denx_cstring*)(ptr))->size > 0)
        {
            return (char*)CStringEnd(ptr);
        }
    }
    return NULL;
}

// Returns the maximum number of characters a CString can hold.
const size_t CStringMaxSize()
{
    return 0;
}

size_t CStringReserve(void* ptr, size_t new_cap)
{
    if(ptr == NULL)
    {
        return 0;
    }

    // shrink request
    if(((denx_cstring*)(ptr))->capacity > new_cap)
    {
        char* temp_str = (char)malloc(new_cap);
        memcpy_s(temp_str, new_cap, ((denx_cstring*)(ptr))->string, ((denx_cstring*)(ptr))->capacity);

        free(((denx_cstring*)(ptr))->string);
        ((denx_cstring*)(ptr))->string = NULL;
        ((denx_cstring*)(ptr))->string = (char*)malloc(new_cap);
        memcpy_s(((denx_cstring*)(ptr))->string, new_cap, temp_str, new_cap);
        ((denx_cstring*)(ptr))->capacity = new_cap;
        return new_cap;
    }
    // shrink-to-fit request
    else if(((denx_cstring*)(ptr))->size > new_cap)
    {
        CStringShrinkToFit(ptr);
        return ((denx_cstring*)(ptr))->capacity;
    }
    else
    {
        if(((denx_cstring*)(ptr))->capacity == new_cap)
        {
            return new_cap;
        }

        // Expanding the string.
        // NOTE: This is the same procedure as if the capacity of the CString is greater than the new capacity.
        //       So we could just use the first if's procedure instead of copying it here.
        char* temp_str = (char)malloc(new_cap);
        memcpy_s(temp_str, new_cap, ((denx_cstring*)(ptr))->string, ((denx_cstring*)(ptr))->capacity);

        free(((denx_cstring*)(ptr))->string);
        ((denx_cstring*)(ptr))->string = NULL;
        ((denx_cstring*)(ptr))->string = (char*)malloc(new_cap);
        memcpy_s(((denx_cstring*)(ptr))->string, new_cap, temp_str, new_cap);
        ((denx_cstring*)(ptr))->capacity = new_cap;
        return new_cap;
    }
    
    return 0;
}

size_t CStringShrinkToFit(void* ptr)
{
    if(ptr == NULL)
    {
        return 0;
    }

    if(((denx_cstring*)(ptr))->capacity == ((denx_cstring*)(ptr))->size)
    {
        return 0;
    }

    size_t new_cap = ((denx_cstring*)(ptr))->size;
    size_t old_cap = ((denx_cstring*)(ptr))->capacity;

    char* temp_str = (char*)malloc(new_cap);
    memcpy_s(temp_str, new_cap, ((denx_cstring*)(ptr))->string, ((denx_cstring*)(ptr))->capacity);

    free(((denx_cstring*)(ptr))->string);
    ((denx_cstring*)(ptr))->string = NULL;
    ((denx_cstring*)(ptr))->string = (char*)malloc(new_cap);
    memcpy_s(((denx_cstring*)(ptr))->string, new_cap, temp_str, new_cap);

    ((denx_cstring*)(ptr))->capacity = new_cap;

    return (old_cap - new_cap); 
}

// TODO: If the index is 0, nothing is inserted(NEEDS IMPLEMENTATION)
// TODO: If the index is greater than 0, a 'Segmentation-Fault' is thrown.
// TODO: Size and length must be updated.
size_t CStringInsert(void* ptr, char c, size_t indx)
{
     if(ptr == NULL)
     {
         return 1;
     }

    // Here we can use `CStringPushBack` instead.
    if(((denx_cstring*)(ptr))->string == NULL)
    {
        // allocate at least 1 byte.
        ((denx_cstring*)(ptr))->string = (char*)malloc(2);
        if(((denx_cstring*)(ptr))->string == NULL)
        {
            return 1;
        }

        ((denx_cstring*)(ptr))->length = 1;
        ((denx_cstring*)(ptr))->size = 2;
        ((denx_cstring*)(ptr))->capacity = 2;
        ((denx_cstring*)(ptr))->string[0] = c;
        ((denx_cstring*)(ptr))->string[1] = '\0';
        return 0;
    }

    // Actually, here we could use `CStringPushBack`.
    if(indx >= ((denx_cstring*)(ptr))->length)
    {
        CStringStaticIncreaseCapacity(ptr);
        ((denx_cstring*)(ptr))->string[((denx_cstring*)(ptr))->length] = c;
        ((denx_cstring*)(ptr))->string[((denx_cstring*)(ptr))->length + 1] = '\0';
        return 0;
    }
    else if(indx < ((denx_cstring*)(ptr))->length)
    {
        if(indx > 0)
        {
            char* temp_str = (char*)malloc(indx + 1);
            for(size_t i = 0; i < indx; i++)
            {
                temp_str[i] = ((denx_cstring*)(ptr))->string[i];
            }
            temp_str[indx] = c;

            char* after_str = (char*)malloc(((denx_cstring*)(ptr))->length - indx);
            
            char* final_rslt = (char*)malloc(((denx_cstring*)(ptr))->capacity);

            strcat_s(final_rslt, indx + 1, temp_str);
            strcat_s(final_rslt, ((denx_cstring*)(ptr))->length - indx, after_str);

            free(after_str);
            free(temp_str);
            after_str = NULL;
            temp_str = NULL;

            strcpy_s(((denx_cstring*)(ptr))->string, ((denx_cstring*)(ptr))->capacity, final_rslt);
            free(final_rslt);
            final_rslt = NULL;
            return 0;
        }
        
    }
    return 0;
}

size_t CStringErase(void* ptr, size_t indx)
{
    if(ptr != NULL && ((denx_cstring*)(ptr))->length >= indx && ((denx_cstring*)(ptr))->string != NULL)
    {
        ((denx_cstring*)(ptr))->string[indx] = '\0';
        return 0;
    }
    return 1;
}

size_t CStringPushBack(void* ptr, char c)
{
    if(ptr == NULL)
    {
        return 1;
    }

    if(CSTRING_REF(ptr)->string == NULL)
    {
        CSTRING_REF(ptr)->string = (char*)malloc(2);
        // error: couldn't allocate memory for string.
        if(CSTRING_REF(ptr)->string == NULL)
        {
            return 1;
        }

        CSTRING_REF(ptr)->string[0] = c;
        CSTRING_REF(ptr)->string[1] = '\0';

        CSTRING_REF(ptr)->capacity = 2;
        CSTRING_REF(ptr)->size = 2;
        CSTRING_REF(ptr)->length = 1;

        return 0;
    }

    size_t orig_size = ((denx_cstring*)(ptr))->size;
    char* temp_str = (char*)malloc(orig_size + 1);

    memcpy(temp_str, ((denx_cstring*)(ptr))->string, orig_size);

    temp_str[orig_size - 1] = c;
    temp_str[orig_size] = '\0';

    free(((denx_cstring*)(ptr))->string);
    ((denx_cstring*)(ptr))->string = NULL;

    ((denx_cstring*)(ptr))->string = (char*)malloc(orig_size + 1);
    memcpy_s(((denx_cstring*)(ptr))->string, orig_size + 1, temp_str, orig_size + 1);
    ((denx_cstring*)(ptr))->size = orig_size + 1;
    ((denx_cstring*)(ptr))->length = strlen(((denx_cstring*)(ptr))->string);

    free(temp_str);
    temp_str = NULL;

    return 0;
}
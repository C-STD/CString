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

}DENX_CString;

void CStringStaticIncreaseCapacity(void*);

void* CStringCreate()
{
    DENX_CString* string = (DENX_CString*)(malloc(sizeof(DENX_CString)));
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
        if(((DENX_CString*)(ptr))->string != NULL)
        {
            free(((DENX_CString*)(ptr))->string);
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
        if(((DENX_CString*)(ptr))->size == 0)
        {
            return i;
        }
        
        for(;;)
        {
            if(((DENX_CString*)(ptr))->string[i++] == '\0')
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
    return ((DENX_CString*)(ptr))->size;
}

size_t CStringCapacity(void* ptr)
{
    return ((DENX_CString*)(ptr))->capacity;
}

char* CStringAt(void* ptr, size_t index)
{
    if(ptr != NULL && index < ((DENX_CString*)(ptr))->size)
    {
        return &((DENX_CString*)(ptr))->string[index];
    }
    return NULL;
}

void CStringClear(void* ptr)
{
    if(ptr != NULL)
    {
        memset(((DENX_CString*)(ptr))->string, 0, ((DENX_CString*)(ptr))->size);
    }
}

void* CStringBegin(void* ptr)
{
    if(ptr != NULL)
    {
        return ((DENX_CString*)(ptr))->begin;
    }
    return NULL;
}

void* CStringEnd(void* ptr)
{
    if(ptr != NULL)
    {
        return ((DENX_CString*)(ptr))->end;
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

        if(((DENX_CString*)(ptr))->string == NULL)
        {
            ((DENX_CString*)(ptr))->string = (char*)malloc(str_len);
            memset(((DENX_CString*)(ptr))->string, 0, str_len);
        }

        strcpy_s(((DENX_CString*)(ptr))->string, str_len + 1, str);
        ((DENX_CString*)(ptr))->length = strlen(((DENX_CString*)(ptr))->string);

        if(((DENX_CString*)(ptr))->length > ((DENX_CString*)(ptr))->size)
        {
            ((DENX_CString*)(ptr))->size = ((DENX_CString*)(ptr))->length + 1;
            CStringStaticIncreaseCapacity(ptr); // Increase the capacity of the string.
        }

        if(!strcmp(((DENX_CString*)(ptr))->string, str))
        {
            return ((DENX_CString*)(ptr))->size; 
        }
    }
    return 0;
}

const char* CStringData(void* ptr)
{
    if(ptr != NULL)
    {
        return ((DENX_CString*)(ptr))->string;
    }
    return NULL;
}

void CStringStaticIncreaseCapacity(void* ptr)
{
    if(ptr != NULL)
    {
        size_t ssize = ((DENX_CString*)(ptr))->size;

        char* temp_str = (char*)malloc(ssize);
        
        size_t ncapacity = ssize + (ssize / 2);

        strcpy_s(temp_str, ssize, ((DENX_CString*)(ptr))->string);

        free(((DENX_CString*)(ptr))->string);
        ((DENX_CString*)(ptr))->string = NULL;

        ((DENX_CString*)(ptr))->string = (char*)malloc(ssize + (ssize / 2));
        strcpy_s(((DENX_CString*)(ptr))->string, ssize, temp_str);
        ((DENX_CString*)(ptr))->capacity = ncapacity;

        free(temp_str);
        temp_str = NULL;
    }
}

size_t CStringEmpty(void* ptr)
{
    if(ptr != NULL)
    {
        return ((DENX_CString*)(ptr))->length;
    }
    return 1;
}
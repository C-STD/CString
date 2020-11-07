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

            ((DENX_CString*)(ptr))->begin = (void*)((DENX_CString*)(ptr))->string;
            ((DENX_CString*)(ptr))->end = (void*)((DENX_CString*)(ptr))->string + str_len;
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

// Returns a pointer to the first character of the CString or NULL.
char* CStringFront(void* ptr)
{
    if(ptr != NULL)
    {
        if(((DENX_CString*)(ptr))->string != NULL && ((DENX_CString*)(ptr))->size > 0)
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
        if(((DENX_CString*)(ptr))->string != NULL && ((DENX_CString*)(ptr))->size > 0)
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
    if(((DENX_CString*)(ptr))->capacity > new_cap)
    {
        char* temp_str = (char)malloc(new_cap);
        memcpy_s(temp_str, new_cap, ((DENX_CString*)(ptr))->string, ((DENX_CString*)(ptr))->capacity);

        free(((DENX_CString*)(ptr))->string);
        ((DENX_CString*)(ptr))->string = NULL;
        ((DENX_CString*)(ptr))->string = (char*)malloc(new_cap);
        memcpy_s(((DENX_CString*)(ptr))->string, new_cap, temp_str, new_cap);
        ((DENX_CString*)(ptr))->capacity = new_cap;
        return new_cap;
    }
    // shrink-to-fit request
    else if(((DENX_CString*)(ptr))->size > new_cap)
    {
        CStringShrinkToFit(ptr);
        return ((DENX_CString*)(ptr))->capacity;
    }
    else
    {
        if(((DENX_CString*)(ptr))->capacity == new_cap)
        {
            return new_cap;
        }

        // Expanding the string.
        // NOTE: This is the same procedure as if the capacity of the CString is greater than the new capacity.
        //       So we could just use the first if's procedure instead of copying it here.
        char* temp_str = (char)malloc(new_cap);
        memcpy_s(temp_str, new_cap, ((DENX_CString*)(ptr))->string, ((DENX_CString*)(ptr))->capacity);

        free(((DENX_CString*)(ptr))->string);
        ((DENX_CString*)(ptr))->string = NULL;
        ((DENX_CString*)(ptr))->string = (char*)malloc(new_cap);
        memcpy_s(((DENX_CString*)(ptr))->string, new_cap, temp_str, new_cap);
        ((DENX_CString*)(ptr))->capacity = new_cap;
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

    if(((DENX_CString*)(ptr))->capacity == ((DENX_CString*)(ptr))->size)
    {
        return 0;
    }

    size_t new_cap = ((DENX_CString*)(ptr))->size;
    size_t old_cap = ((DENX_CString*)(ptr))->capacity;

    char* temp_str = (char*)malloc(new_cap);
    memcpy_s(temp_str, new_cap, ((DENX_CString*)(ptr))->string, ((DENX_CString*)(ptr))->capacity);

    free(((DENX_CString*)(ptr))->string);
    ((DENX_CString*)(ptr))->string = NULL;
    ((DENX_CString*)(ptr))->string = (char*)malloc(new_cap);
    memcpy_s(((DENX_CString*)(ptr))->string, new_cap, temp_str, new_cap);

    ((DENX_CString*)(ptr))->capacity = new_cap;

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
    if(((DENX_CString*)(ptr))->string == NULL)
    {
        // allocate at least 1 byte.
        ((DENX_CString*)(ptr))->string = (char*)malloc(2);
        if(((DENX_CString*)(ptr))->string == NULL)
        {
            return 1;
        }

        ((DENX_CString*)(ptr))->length = 1;
        ((DENX_CString*)(ptr))->size = 2;
        ((DENX_CString*)(ptr))->capacity = 2;
        ((DENX_CString*)(ptr))->string[0] = c;
        ((DENX_CString*)(ptr))->string[1] = '\0';
        return 0;
    }

    // Actually, here we could use `CStringPushBack`.
    if(indx >= ((DENX_CString*)(ptr))->length)
    {
        CStringStaticIncreaseCapacity(ptr);
        ((DENX_CString*)(ptr))->string[((DENX_CString*)(ptr))->length] = c;
        ((DENX_CString*)(ptr))->string[((DENX_CString*)(ptr))->length + 1] = '\0';
        return 0;
    }
    else if(indx < ((DENX_CString*)(ptr))->length)
    {
        if(indx > 0)
        {
            char* temp_str = (char*)malloc(indx + 1);
            for(size_t i = 0; i < indx; i++)
            {
                temp_str[i] = ((DENX_CString*)(ptr))->string[i];
            }
            temp_str[indx] = c;

            char* after_str = (char*)malloc(((DENX_CString*)(ptr))->length - indx);
            
            char* final_rslt = (char*)malloc(((DENX_CString*)(ptr))->capacity);

            strcat_s(final_rslt, indx + 1, temp_str);
            strcat_s(final_rslt, ((DENX_CString*)(ptr))->length - indx, after_str);

            free(after_str);
            free(temp_str);
            after_str = NULL;
            temp_str = NULL;

            strcpy_s(((DENX_CString*)(ptr))->string, ((DENX_CString*)(ptr))->capacity, final_rslt);
            free(final_rslt);
            final_rslt = NULL;
            return 0;
        }
        
    }
    return 0;
}

size_t CStringErase(void* ptr, size_t indx)
{
    if(ptr != NULL && ((DENX_CString*)(ptr))->length >= indx && ((DENX_CString*)(ptr))->string != NULL)
    {
        ((DENX_CString*)(ptr))->string[indx] = '\0';
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

    size_t orig_size = ((DENX_CString*)(ptr))->size;
    char* temp_str = (char*)malloc(orig_size + 1);

    memcpy(temp_str, ((DENX_CString*)(ptr))->string, orig_size);

    temp_str[orig_size - 1] = c;
    temp_str[orig_size] = '\0';

    free(((DENX_CString*)(ptr))->string);
    ((DENX_CString*)(ptr))->string = NULL;

    ((DENX_CString*)(ptr))->string = (char*)malloc(orig_size + 1);
    memcpy_s(((DENX_CString*)(ptr))->string, orig_size + 1, temp_str, orig_size + 1);
    ((DENX_CString*)(ptr))->size = orig_size + 1;
    ((DENX_CString*)(ptr))->length = strlen(((DENX_CString*)(ptr))->string);

    free(temp_str);
    temp_str = NULL;
    
    return 0;
}
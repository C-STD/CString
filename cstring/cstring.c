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
#define CSTRING_LEN(ptr) strlen(CSTRING_REF(ptr)->string)

/* __unix__ is usually defined by compilers targeting Unix systems */
#if defined(__unix__) || defined(__linux__)
    #define CSTRING_STRCAT(_Destination, _SizeInBytes, _Source) strcat(_Destination, _Source)
    #define CSTRING_STRCPY(_Destination, _SizeInBytes, _Source) strcpy(_Destination, _Source)
    #define CSTRING_MEMCPY(_Destination, _DestinationSize, _Source, _SourceSize) memcpy(_Destination, _Source, _SourceSize)
/* _Win32 is usually defined by compilers targeting 32 or   64 bit Windows systems */
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    #define CSTRING_STRCAT(_Destination, _SizeInBytes, _Source) strcat_s(_Destination, _SizeInBytes, _Source)
    #define CSTRING_STRCPY(_Destination, _SizeInBytes, _Source) strcpy_s(_Destination, _SizeInBytes, _Source)
    #define CSTRING_MEMCPY(_Destination, _DestinationSize, _Source, _SourceSize) memcpy_s(_Destination, _DestinationSize, _Source, _SourceSize)
#else
    #error "unknown compiler or platform. supported platforms are: `Linux` and `Windows`"
#endif

void CStringStaticIncreaseCapacity(void*);

void* CStringCreate()
{
    denx_cstring* string = (denx_cstring*)calloc(1, sizeof(denx_cstring));
    return (void*)string;
}

size_t CStringDestroy(void* ptr)
{
    if(ptr != NULL)
    {
        if(CSTRING_REF(ptr)->string != NULL)
        {
            free(CSTRING_REF(ptr)->string);
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
        return CSTRING_LEN(ptr);
    }
    return 0;
}

size_t CStringSize(void* ptr)
{
    if(ptr != NULL)
    {
        return CSTRING_REF(ptr)->size;
    }
    return 0;
}

size_t CStringCapacity(void* ptr)
{
    if(ptr != NULL)
    {
        return CSTRING_REF(ptr)->capacity;
    }
    return 0;
}

char* CStringAt(void* ptr, size_t index)
{
    if(ptr != NULL && index < CSTRING_REF(ptr)->size)
    {
        return &CSTRING_REF(ptr)->string[index];
    }
    return NULL;
}

void CStringClear(void* ptr)
{
    if(ptr != NULL)
    {
        memset(CSTRING_REF(ptr)->string, 0, CSTRING_REF(ptr)->size);
        CSTRING_REF(ptr)->size = 0;
        CSTRING_REF(ptr)->length = 0;
    }
}

void* CStringBegin(void* ptr)
{
    if(ptr != NULL)
    {
        return CSTRING_REF(ptr)->begin;
    }
    return NULL;
}

void* CStringEnd(void* ptr)
{
    if(ptr != NULL)
    {
        return CSTRING_REF(ptr)->end;
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

        if(CSTRING_REF(ptr)->string == NULL)
        {
            CSTRING_REF(ptr)->string = (char*)calloc(1, str_len);

            CSTRING_REF(ptr)->begin = (void*)CSTRING_REF(ptr)->string;
            CSTRING_REF(ptr)->end = (void*)CSTRING_REF(ptr)->string + str_len;
        }

        CSTRING_STRCPY(CSTRING_REF(ptr)->string, str_len + 1, str);
        CSTRING_REF(ptr)->length = str_len;

        if(CSTRING_REF(ptr)->length > CSTRING_REF(ptr)->size &&
           CSTRING_REF(ptr)->capacity < CSTRING_REF(ptr)->length)
        {
            CSTRING_REF(ptr)->size = CSTRING_REF(ptr)->length + 1;
            CStringStaticIncreaseCapacity(ptr); // Increase the capacity of the string.
        }

        if(!strcmp(CSTRING_REF(ptr)->string, str))
        {
            return CSTRING_REF(ptr)->size; 
        }
    }
    return 0;
}

const char* CStringData(void* ptr)
{
    if(ptr != NULL)
    {
        return CSTRING_REF(ptr)->string;
    }
    return NULL;
}

void CStringStaticIncreaseCapacity(void* ptr)
{
    if(ptr != NULL)
    {
        size_t ssize = CSTRING_REF(ptr)->size;

        char* temp_str = (char*)malloc(ssize);
        
        size_t ncapacity = ssize + (ssize / 2);

        CSTRING_STRCPY(temp_str, ssize, CSTRING_REF(ptr)->string);

        free(CSTRING_REF(ptr)->string);
        CSTRING_REF(ptr)->string = NULL;

        CSTRING_REF(ptr)->string = (char*)malloc(ssize + (ssize / 2));
        CSTRING_STRCPY(CSTRING_REF(ptr)->string, ssize, temp_str);
        CSTRING_REF(ptr)->capacity = ncapacity;

        free(temp_str);
        temp_str = NULL;
    }
}

size_t CStringEmpty(void* ptr)
{
    if(ptr != NULL)
    {
        return CSTRING_REF(ptr)->length;
    }
    return 1;
}

// Returns a pointer to the first character of the CString or NULL.
char* CStringFront(void* ptr)
{
    if(ptr != NULL)
    {
        if(CSTRING_REF(ptr)->string != NULL && CSTRING_REF(ptr)->size > 0)
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
        if(CSTRING_REF(ptr)->string != NULL && CSTRING_REF(ptr)->size > 0)
        {
            return (char*)(CStringEnd(ptr) - 1);
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
    if(CSTRING_REF(ptr)->capacity > new_cap)
    {
        char* temp_str = (char*)calloc(1, new_cap);
        memcpy(temp_str, CSTRING_REF(ptr)->string, new_cap);

        free(CSTRING_REF(ptr)->string);
        CSTRING_REF(ptr)->string = NULL;

        CSTRING_REF(ptr)->string = (char*)calloc(1, new_cap);
        memcpy(CSTRING_REF(ptr)->string, temp_str, new_cap);
        CSTRING_REF(ptr)->capacity = new_cap;

        // we also need to check if the last character is is not a `\0`.
        // otherwise(possibly), when printing the string, we would go behond the size of the string.
        if(CSTRING_REF(ptr)->string[new_cap - 1] != '\0')
        {
            CSTRING_REF(ptr)->string[new_cap - 1] = '\0';
        }
        CSTRING_REF(ptr)->size = CSTRING_LEN(ptr) + 1;
        CSTRING_REF(ptr)->length = CSTRING_LEN(ptr);

        return new_cap;
    }
    // shrink-to-fit request
    else if(CSTRING_REF(ptr)->size > new_cap)
    {
        CStringShrinkToFit(ptr);
        return CSTRING_REF(ptr)->capacity;
    }
    else
    {
        if(CSTRING_REF(ptr)->capacity == new_cap)
        {
            return new_cap;
        }

        // Expanding the string.
        char* temp_str = (char*)calloc(1, new_cap);
        memcpy(temp_str, CSTRING_REF(ptr)->string, CSTRING_REF(ptr)->capacity);

        free(CSTRING_REF(ptr)->string);
        CSTRING_REF(ptr)->string = NULL;
        CSTRING_REF(ptr)->string = (char*)calloc(1, new_cap);

        memcpy(CSTRING_REF(ptr)->string, temp_str, new_cap);
        CSTRING_REF(ptr)->capacity = new_cap;
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

    if(CSTRING_REF(ptr)->capacity == CSTRING_REF(ptr)->size)
    {
        return 0;
    }

    size_t new_cap = CSTRING_REF(ptr)->size;
    size_t old_cap = CSTRING_REF(ptr)->capacity;

    char* temp_str = (char*)malloc(new_cap);
    CSTRING_MEMCPY(temp_str, new_cap, CSTRING_REF(ptr)->string, CSTRING_REF(ptr)->capacity);

    free(CSTRING_REF(ptr)->string);
    CSTRING_REF(ptr)->string = NULL;
    CSTRING_REF(ptr)->string = (char*)malloc(new_cap);
    CSTRING_MEMCPY(CSTRING_REF(ptr)->string, new_cap, temp_str, new_cap);

    CSTRING_REF(ptr)->capacity = new_cap;

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
    if(CSTRING_REF(ptr)->string == NULL)
    {
        // allocate at least 1 byte.
        CSTRING_REF(ptr)->string = (char*)malloc(2);
        if(CSTRING_REF(ptr)->string == NULL)
        {
            return 1;
        }

        CSTRING_REF(ptr)->length = 1;
        CSTRING_REF(ptr)->size = 2;
        CSTRING_REF(ptr)->capacity = 2;
        CSTRING_REF(ptr)->string[0] = c;
        CSTRING_REF(ptr)->string[1] = '\0';
        return 0;
    }

    // Actually, here we could use `CStringPushBack`.
    if(indx >= CSTRING_REF(ptr)->length)
    {
        CStringStaticIncreaseCapacity(ptr);
        CSTRING_REF(ptr)->string[CSTRING_REF(ptr)->length] = c;
        CSTRING_REF(ptr)->string[CSTRING_REF(ptr)->length + 1] = '\0';
        return 0;
    }
    else if(indx < CSTRING_REF(ptr)->length)
    {
        if(indx > 0)
        {
            char* temp_str = (char*)malloc(indx + 1);
            for(size_t i = 0; i < indx; i++)
            {
                temp_str[i] = CSTRING_REF(ptr)->string[i];
            }
            temp_str[indx] = c;

            char* after_str = (char*)malloc(CSTRING_REF(ptr)->length - indx);
            
            char* final_rslt = (char*)malloc(CSTRING_REF(ptr)->capacity);

            CSTRING_STRCAT(final_rslt, indx + 1, temp_str);
            CSTRING_STRCAT(final_rslt, CSTRING_REF(ptr)->length - indx, after_str);

            free(after_str);
            free(temp_str);
            after_str = NULL;
            temp_str = NULL;

            CSTRING_STRCPY(CSTRING_REF(ptr)->string, CSTRING_REF(ptr)->capacity, final_rslt);
            free(final_rslt);
            final_rslt = NULL;
            return 0;
        }
        
    }
    return 0;
}

size_t CStringErase(void* ptr, size_t indx)
{
    if(ptr == NULL || indx > CSTRING_REF(ptr)->size)
    {
        return 1;
    }

    if(indx == (CSTRING_REF(ptr)->length - 1))
    {
        CSTRING_REF(ptr)->string[indx] = '\0';
        CSTRING_REF(ptr)->length--;
        CSTRING_REF(ptr)->size--;
        return 0;
    }
    else
    {
        if(!indx) { indx = 1; }

        while(indx != 0)
        {
            for(size_t i = 1; CSTRING_REF(ptr)->string[i] != '\0' && i < CSTRING_REF(ptr)->length; i++)
            {
                CSTRING_REF(ptr)->string[i - 1] = CSTRING_REF(ptr)->string[i];
                // CSTRING_REF(ptr)->string[indx] = CSTRING_REF(ptr)->string[indx + 1];
            }
            indx--;
        }
        CSTRING_REF(ptr)->length--;
        CSTRING_REF(ptr)->size--;
        CSTRING_REF(ptr)->string[CSTRING_REF(ptr)->length] = '\0';
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

    size_t orig_size = CSTRING_REF(ptr)->size;
    char* temp_str = (char*)malloc(orig_size + 1);

    memcpy(temp_str, CSTRING_REF(ptr)->string, orig_size);

    temp_str[orig_size - 1] = c;
    temp_str[orig_size] = '\0';

    free(CSTRING_REF(ptr)->string);
    CSTRING_REF(ptr)->string = NULL;

    CSTRING_REF(ptr)->string = (char*)malloc(orig_size + 1);
    CSTRING_MEMCPY(CSTRING_REF(ptr)->string, orig_size + 1, temp_str, orig_size + 1);
    CSTRING_REF(ptr)->size = orig_size + 1;
    CSTRING_REF(ptr)->length = strlen(CSTRING_REF(ptr)->string);

    free(temp_str);
    temp_str = NULL;

    return 0;
}

size_t CStringPopBack(void* ptr)
{
    if(ptr != NULL)
    {
        return CStringErase(ptr, CStringLength(ptr) - 1);
    }
    return 1;
}

size_t CStringAppend(void* ptr, char c)
{
    return CStringPushBack(ptr, c);
}

int CStringCompare(void* ptr0, void* ptr1)
{
    if(ptr0 == NULL || ptr1 == NULL)
    {
        return -1;
    }

    while(*CSTRING_REF(ptr0)->string)
    {
        if(*CSTRING_REF(ptr0)->string != *CSTRING_REF(ptr1)->string)
        {
            break;
        }
        CSTRING_REF(ptr0)->string++;
        CSTRING_REF(ptr1)->string;
    }
    return *(const unsigned char*)CSTRING_REF(ptr0)->string - *(const unsigned char*)CSTRING_REF(ptr1)->string;
}
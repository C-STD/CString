#ifndef DENX_CSTRING
#define DENX_CSTRING

#include <stdio.h>

// Create an empty CString object and returns a pointer to its data.
void* CStringCreate();

// Destroys the CString and returns a 0(no error) or 1(error).
size_t CStringDestroy(void*);

// Calculates the length of the CString and returns it.
size_t CStringLength(void*);

// Calculates the size of the CString and returns it. Note: unlike `CStringLength`, this will calculate the actual size of the string in memory.
size_t CStringSize(void*);

// Calculates the capacity of the CString object and returns it.
size_t CStringCapacity(void*);

// Returns a pointer to a character of the string or `NULL` if the index isn't valid.
char* CStringAt(void*, size_t);

// Clears the CString. This won't affect its capacity and size.
void CStringClear(void*);

// Returns a pointer to the first character of the CString.
void* CStringBegin(void*);

// Returns a pointer to the last character of the CString.
void* CStringEnd(void*);

// Returns a pointer to the last character of the CString(reversed beginning).
void* CStringRBegin(void*);

// Returns a pointer to the first character of the CString(reversed ending).
void* CStringREnd(void*);

// Copies the content of the string passed as argument to the CString. Returns the number of bytes copied.
size_t CStringEqual(void*, const char*);

// Returns the actual string of the CString object.
const char* CStringData(void*);

// Check if the CString is empty. Returns 0(not empty) or 1(empty). If CString is `NULL`, 1 is returned.
size_t CStringEmpty(void*);

// Returns a pointer to the first character of the CString or NULL.
char* CStringFront(void*);

// Returns a pointer to the last character of the CString or NULL.
char* CStringBack(void*);

// Returns the maximum number of characters a CString can hold. For the time being, this function will return 0. At the moment I don't know where could I find the maximum number of characters of a string in C.
const size_t CStringMaxSize();

#endif
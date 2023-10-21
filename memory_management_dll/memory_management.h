#pragma once


#ifdef MEMORYMANAGEMENT_EXPORTS
#define MEMORYMANAGEMENT_API __declspec(dllexport)
#else
#define MEMORYMANAGEMENT_API __declspec(dllimport)
#endif


MEMORYMANAGEMENT_API void* my_malloc(size_t _Size, int);

MEMORYMANAGEMENT_API void* my_calloc(size_t num_elements, size_t element_size, int);

MEMORYMANAGEMENT_API void* my_realloc(void* ptr, size_t size, int);

MEMORYMANAGEMENT_API void my_free(void* memory, int);

MEMORYMANAGEMENT_API void my_free_all(void);


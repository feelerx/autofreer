#include "pch.h"
#include <stdio.h>	
#include <stdbool.h>
#include <windows.h>
#include <errno.h>
#include <stdint.h>
#include "memory_management.h"

#define MAX_SIZE 10

// Define appropriate data types
typedef unsigned int uint;
typedef DWORD dword;
typedef unsigned char uchar;

HANDLE create_heap(uint32_t);
void destroy_heap(void);

// Define new function name
uchar map_error_code(dword error_code);

HANDLE hHeap[MAX_SIZE];
int hHeapCounter = 0;

struct info {
    void* memory_name;
    int memory_num;
};
struct info infor[MAX_SIZE];

void* my_malloc(size_t _Size, int temp)
{
    LPVOID pvVar2;
    SIZE_T dwBytes;

    hHeapCounter = temp;

    create_heap(1);
    if (hHeap[hHeapCounter] != (HANDLE)0x0) {
        if (_Size < 0xffffffffffffffe1) {
            dwBytes = 1;
            if (_Size != 0) {
                dwBytes = _Size;
            }
            while (true) {
                pvVar2 = HeapAlloc(hHeap[hHeapCounter], 0, dwBytes);
                if (pvVar2 != (LPVOID)0x0) {
                    infor[hHeapCounter].memory_name = pvVar2;
                    infor[hHeapCounter].memory_num = hHeapCounter;
                    return pvVar2;
                }
            }
            errno = ENOMEM;
        }
        else {
            errno = ENOMEM;
        }
    }
    else {
        // _FF_MSGBANNER();
        // FUN_11013c304(0x1e);
        // FUN_11013a140(0xff);
    }
    return (void*)0x0;
}


HANDLE create_heap(uint32_t param_1)
{
    HANDLE HeapHandle;
    uint32_t local_res8[8];

    local_res8[0] = param_1;
    HeapHandle = HeapCreate(0, 0x1000, 0);
    hHeap[hHeapCounter] = HeapHandle;
    //hHeapCounter++;
    if (HeapHandle != (HANDLE)0x0) {
        local_res8[0] = 2;
        HeapSetInformation(HeapHandle, HeapCompatibilityInformation, local_res8, 4);
        local_res8[0] = 2;
        HeapSetInformation(hHeap, HeapCompatibilityInformation, local_res8, 4);
        HeapHandle = (HANDLE)0x1;
    }
    return HeapHandle;
}

void destroy_heap(void)

{
    HeapDestroy(hHeap[hHeapCounter]);
    hHeap[hHeapCounter] = (HANDLE)0x0;
    return;
}

void my_free(void* _Memory, int temp)
{
    hHeapCounter = temp;
    if (_Memory != NULL) {
        //hHeapCounter--;
        BOOL success = HeapFree(hHeap[hHeapCounter], 0, _Memory);
        if (!success) {
            int* pErrno = _errno();
            *pErrno = map_error_code(GetLastError());
        }
        else {
            destroy_heap();
            infor[hHeapCounter].memory_name = (HANDLE)0x0;
            infor[hHeapCounter].memory_num = NULL;
        }
    }
}

void my_free_all(void) {
    for (int i = 0; i < MAX_SIZE; i++) {
        if (infor[i].memory_name == (HANDLE)0x0) continue;
        my_free(infor[i].memory_name, infor[i].memory_num);
    }
    return;
}


// Map error code to errno value
uchar map_error_code(dword error_code)
{
    const int KNOWN_ERROR_CODES[] = { -1 /* unknown */, 0x12, 0x5, 0x6, 0x11, 0x18, 0x14, 0x2, 0x13, 0x7, 0x9, 0x17, 0x8, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf, 0x10, 0x15, 0x16 };
    const uchar KNOWN_ERROR_VALUES[] = { 0x16, 0x7, 0x8, 0x9, 0xa, 0xb, 0xc, 0xd, 0x7, 0xe, 0xf, 0x16, 0x7, 0x16, 0x16, 0x16, 0xd, 0xd, 0xd, 0xd, 0x16, 0x16 };

    const int UNKNOWN_ERROR_MIN = 0x13U;
    const int UNKNOWN_ERROR_MAX = 0xbcU;
    const uchar UNKNOWN_ERROR_VALUE = 0x16;

    uint i = 0;

    // Check for known error codes
    while (i < sizeof(KNOWN_ERROR_CODES) / sizeof(KNOWN_ERROR_CODES[0]))
    {
        if (error_code == KNOWN_ERROR_CODES[i])
        {
            return KNOWN_ERROR_VALUES[i];
        }
        i++;
    }

    // Check for custom error codes
    if (error_code >= UNKNOWN_ERROR_MIN && error_code <= UNKNOWN_ERROR_MAX)
    {
        return UNKNOWN_ERROR_VALUE;
    }
    else
    {
        // Unknown error code
        return UNKNOWN_ERROR_VALUE;
    }
}

void* my_realloc(void* ptr, size_t new_size, int temp) {
    int errno_val;
    DWORD last_error;
    void* new_ptr;
    HANDLE heap_handle;
    int* errno_ptr;
    hHeapCounter = temp;

    // If ptr is NULL, equivalent to calling malloc(new_size)
    if (ptr == NULL) {
        new_ptr = my_malloc(new_size, temp);
    }
    else {
        // If new_size is 0, equivalent to calling free(ptr)
        if (new_size == 0) {
            my_free(ptr, temp);
        }
        else {
            // If new_size is within the limit
            if (new_size < (SIZE_MAX - 16)) {
                do {
                    // If new_size is 0, set it to 1
                    if (new_size == 0) {
                        new_size = 1;
                    }

                    // Get handle to the heap that ptr belongs to and attempt to reallocate memory block
                    //if (IsBadReadPtr(ptr, sizeof(void*)))  printf("\nBAD READ");

                    //SIZE_T heap_info = HeapQueryInformation(ptr, HeapCompatibilityInformation, &heap_handle, sizeof(heap_handle), NULL);
                    //printf("\nptr address:%p\nheapinfo:%d \nheaphanle:%d\n", ptr, heap_info, sizeof(heap_handle));
                    //if (heap_info == 0) {
                    //    last_error = GetLastError();
                    //    printf("HeapQueryInformation failed with error code: %d\n", last_error);
                    //    break;
                   // }
                    new_ptr = HeapReAlloc(hHeap[hHeapCounter], 0, ptr, new_size);
                    int error_code = GetLastError();
                    printf("%d", error_code);

                    // If reallocation was successful, return pointer to new memory block
                    if (new_ptr != NULL) {
                        return new_ptr;
                    }

                    // If reallocation was unsuccessful and no new handler was installed, return NULL
                    errno_ptr = _errno();
                    last_error = GetLastError();
                    errno_val = map_error_code(last_error);
                    *errno_ptr = errno_val;

                    // Attempt to call new handler
                    errno_val = _callnewh(new_size);

                    // If new handler call was unsuccessful, set errno and handle the error
                    if (errno_val == 0) {
                        errno_ptr = _errno();
                        last_error = GetLastError();
                        errno_val = map_error_code(last_error);
                        *errno_ptr = errno_val;
                        break;
                    }
                } while (new_size < (SIZE_MAX - 16));
            }

            // If new_size exceeds the limit, set errno to ENOMEM
            _callnewh(new_size);
            errno_ptr = _errno();
            *errno_ptr = ENOMEM;
        }
    }

    new_ptr = NULL;
    return new_ptr;
}

void* my_calloc(size_t num_elements, size_t element_size, int temp)
{
    LPVOID pvVar2;
    SIZE_T dwBytes;

    hHeapCounter = temp;

    create_heap(1);
    if (hHeap[hHeapCounter] != (HANDLE)0x0) {
        if (num_elements < 0xffffffffffffffe1) {
            dwBytes = num_elements * element_size; // Calculate total bytes needed
            if (dwBytes != 0) {
                pvVar2 = HeapAlloc(hHeap[hHeapCounter], HEAP_ZERO_MEMORY, dwBytes); // Use HEAP_ZERO_MEMORY flag to zero-initialize the memory
                if (pvVar2 != (LPVOID)0x0) {
                    infor[hHeapCounter].memory_name = pvVar2;
                    infor[hHeapCounter].memory_num = hHeapCounter;
                    return pvVar2;
                }
            }
            errno = ENOMEM;
        }
        else {
            errno = ENOMEM;
        }
    }
    else {
        // _FF_MSGBANNER();
        // FUN_11013c304(0x1e);
        // FUN_11013a140(0xff);
    }
    return (void*)0x0;
}


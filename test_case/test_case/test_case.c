

#include <stdio.h>
#include "memory_management.h"

int main(void) {

    int* ptr = (int*)my_malloc(sizeof(int), 0);
    int* utr = (int*)my_malloc(sizeof(int), 1);
    int* vtr = (int*)my_malloc(sizeof(int), 2);
    int* wtr = (int*)my_malloc(sizeof(int), 3);
    if (ptr == NULL) {
        printf("Failed to allocate memory!\n");
        return 1;
    }
    *ptr = 42;
    *utr = 32; 
    *vtr = 22;
    *wtr = 12;

    printf("***          MALLOC TEST SECTION\n\n");

    printf("The value of ptr is: %d at location: %p\n", *ptr, ptr);
    printf("The value of utr is: %d at location: %p\n", *utr, utr);
    printf("The value of vtr is: %d at location: %p\n", *vtr, vtr);
    printf("The value of wtr is: %d at location: %p\n", *wtr, wtr);

    printf("\n***          MALLOC TEST SUCCESSFUL!\n\n");


    printf("\n***          WE FREE VTR and try to print its value\n");
    printf("\n***          NOTICE THE ERROR CODE\n");
    printf("\n***   error code - 1073741819 means we tried to access a memory address that is not available\n");
    printf("\n***          FREE TEST SUCCESSFUL!!\n\n");

    my_free(vtr, 2);
    //printf("The value of vtr is: %d at location: %p\n", *vtr, vtr);
   
    int* newPtr = my_realloc(utr, 10 * sizeof(int), 1);
    if (newPtr == NULL) {
        printf("Memory reallocation failed\n");
        my_free(ptr, 0); // Clean up the original memory block
        return 1;
    }

    printf("\n***         NEXT, WE USE REALLOC ON UTR\n");
    printf("\n***         WE INCREASE ITS SIZE FROM THAT OF A SINGLE INT TO AN ARRAY OF SIZE 10*SIZEOF(INT)\n");

    printf("\n***          REALLOCATED MEMORY BLOCK'S NEW CONTENT: \n");
    for (int i = 0; i < 10; i++) {
        newPtr[i] = i; // Assign values
        printf("%d      ", newPtr[i]);
    }

    printf("\n\n***             REALLOC SUCCESSFUL!!!\n\n");

    printf("\n***       CALLOC INITIALIZES CREATED BLOCKS WITH A VALUE OF NULL \n");

    int* arr = (int*)my_calloc(5, sizeof(int), 3);

    if (arr != NULL) {

        printf("\n***       printing the values automatically alloted by calloc:\n");
        for (int i = 0; i < 5; i++) {
            printf("%d      ", arr[i]);
        }
        printf("\n***       we now modify the values with numbers 1-5:\n");

        for (int i = 0; i < 5; i++) {
            arr[i] = i + 1;
        }

        for (int i = 0; i < 5; i++) {
            printf("%d      ", arr[i]);
        }
        printf("\n\n***         CALLOC SUCCESSFUL!!!!\n\n");

    } 
    
    //my_free_all();
    my_free_all();
 

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

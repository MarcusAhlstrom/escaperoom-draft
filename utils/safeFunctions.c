#include "safeFunctions.h"

/**
 * Validate dynamically allocated memory
 */
 void validateAllocation(void *input){
    if(input == NULL){
        fprintf(stderr, "Allocation Problem\n");
        perror(" ");
        exit(EXIT_FAILURE);
    }
}

/**
 * Function that safely reallocates memory and handle error checking
 */
void *safeRealloc(void *input, int size){
    void *ret = realloc(input, size);
    validateAllocation(ret);
    return ret;
}

/**
 * Function that safely allocates memory and handle error checking
 */
void *safeCalloc(int size1, int size2){
    void *ret = calloc(size1, size2);
    validateAllocation(ret);
    return ret;
}

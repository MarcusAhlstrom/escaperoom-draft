#ifndef SAFE_FUNC
#define SAFE_FUN

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
/**
 * Validate dynamically allocated memory
 *
 * @param input     void pointer to check
 * @return err      Exits with EXIT_FAILURE
 * @return void     Nothing
 */
void validateAllocation(void *input);

/**
 * Function that safely reallocates memory and handle error checking
 *
 * @param input size    void pointer to check and size of new allocation
 * @return err          Exits with EXIT_FAILURE
 * @return void*        Void pointer to new allocation
 */
void *safeRealloc(void *input, int size);

/**
 * Function that safely allocates memory and handle error checking
 *
 * @param size1 size2   size1 number of datatypes and size2 size of datatype
 * @return err          Exits with EXIT_FAILURE
 * @return void*        Void pointer to new allocation
 */
void *safeCalloc(int size1, int size2);

#endif

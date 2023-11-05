#include "shell.h"
/**
 * my_free - Frees a pointer and NULLs the address
 * @ptr_address: Address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int my_free(void **ptr_address)
{
    if (ptr_address && *ptr_address)
    {
        free(*ptr_address);
        *ptr_address = NULL;
        return 1;
    }
    return 0;
}

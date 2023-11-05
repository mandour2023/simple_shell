#include "shell.h"

/**
 * custom_memset - Fills memory with a constant byte
 * @str: The pointer to the memory area
 * @c: The byte to fill *str with
 * @size: The amount of bytes to be filled
 *
 * Return: Pointer to the memory area str
 */
char *custom_memset(char *str, char c, unsigned int size)
{
    unsigned int i;

    for (i = 0; i < size; i++)
        str[i] = c;
    return str;
}

/**
 * custom_free_strings - Frees a string of strings
 * @str_array: String of strings
 */
void custom_free_strings(char **str_array)
{
    char **temp = str_array;

    if (!str_array)
        return;
    while (*str_array)
        free(*str_array++);
    free(temp);
}

/**
 * custom_reallocate - Reallocates a block of memory
 * @prev_ptr: Pointer to the previously allocated block
 * @prev_size: Byte size of the previous block
 * @new_size: Byte size of the new block
 *
 * Return: Pointer to the new block
 */
void *custom_reallocate(void *prev_ptr, unsigned int prev_size, unsigned int new_size)
{
    char *new_ptr;

    if (!prev_ptr)
        return malloc(new_size);
    if (!new_size)
        return (free(prev_ptr), NULL);
    if (new_size == prev_size)
        return prev_ptr;

    new_ptr = malloc(new_size);
    if (!new_ptr)
        return NULL;

    prev_size = prev_size < new_size ? prev_size : new_size;
    while (prev_size--)
        new_ptr[prev_size] = ((char *)prev_ptr)[prev_size];
    free(prev_ptr);
    return new_ptr;
}

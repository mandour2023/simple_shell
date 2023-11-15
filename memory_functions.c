#include "shell.h"

/**
 **_mymset - fills memory with a constant byte
 *@str: the pointer to the memory area
 *@ch: the byte to fill *str with
 *@len: the amount of bytes to be filled
 *Return: (str) a pointer to the memory area str
 */
char *_mymset(char *str, char ch, unsigned int len)
{
	unsigned int i;

	for (i = 0; i < len; i++)
		str[i] = ch;
	return (str);
}

/**
 * myffree - frees a string of strings
 * @ptr: string of strings
 */
void myffree(char **ptr)
{
	char **arr = ptr;

	if (!ptr)
		return;
	while (*ptr)
		free(*ptr++);
	free(arr);
}

/**
 * my_realloc - reallocates a block of memory
 * @p: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *my_realloc(void *p, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;

	if (!p)
		return (malloc(new_size));
	if (!new_size)
		return (free(p), NULL);
	if (new_size == old_size)
		return (p);

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		new_ptr[old_size] = ((char *)p)[old_size];
	free(p);
	return (new_ptr);
}

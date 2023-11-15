#include "shell.h"

/**
 **_strncpy - duplicates a string
 *@dst: the destination string to be duplicated to
 *@src: the source string
 *@n: the number of characters to be duplicated
 *Return: the duplicated string
 */
char *_strncpy(char *dst, char *src, int n)
{
	int i, j;
	char *s = dst;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dst[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dst[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenates two strings
 *@dst: the first string
 *@src: the second string
 *@n: the maximum number of bytes to be used
 *Return: the concatenated string
 */
char *_strncat(char *dst, char *src, int n)
{
	int i, j;
	char *s = dst;

	i = 0;
	j = 0;
	while (dst[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dst[i] = '\0';
	return (s);
}

/**
 **_strchr - locates a character in a string
 *@str: the string to be parsed
 *@chr: the character to look for
 *Return: (str) a pointer to the memory area str
 */
char *_strchr(char *str, char chr)
{
	do {
		if (*str == chr)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}

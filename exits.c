#include "shell.h"

/**
 **_sncpy - copies a string
 *@d: the destination string to be copied to
 *@s: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_sncpy(char *d, char *s, int n)
{
	int i, j;
	char *str = d;

	i = 0;
	while (s[i] != '\0' && i < n - 1)
	{
		d[i] = s[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			d[j] = '\0';
			j++;
		}
	}
	return (str);
}

/**
 **_sncat - concatenates two strings
 *@d: the first string
 *@s: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_sncat(char *d, char *s, int n)
{
	int i, j;
	char *str = d;

	i = 0;
	j = 0;
	while (d[i] != '\0')
		i++;
	while (s[j] != '\0' && j < n)
	{
		d[i] = s[j];
		i++;
		j++;
	}
	if (j < n)
		d[i] = '\0';
	return (str);
}

/**
 **_schr - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_schr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

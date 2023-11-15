#include "shell.h"

/**
 * custom_strlen - returns the length of a string
 * @stri: the string whose length to check
 * _strln - returns the length of a string
 * @str: the string whose length to check
 *
 * Return: integer length of string
 */
int custom_strlen(char *stri)
int _strln(char *str)
{
    int length = 0;
	int i = 0;

    if (!stri)
        return (0);
	if (!str)
		return (0);

    while (*stri++)
        length++;
    return length;
	while (*str++)
		i++;
	return (i);
}

/**
 * custom_strcmp - performs lexicographic comparison of two strings.
 * @stri1: the first string
 * @stri2: the second string
 * _strcp - performs lexicogarphic comparison of two strangs.
 * @s1: the first strang
 * @s2: the second strang
 *
 * Return: negative if stri1 < stri2, positive if stri1 > stri2, zero if stri1 == stri2
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int custom_strcmp(char *stri1, char *stri2)
int _strcp(char *s1, char *s2)
{
    while (*stri1 && *stri2)
    {
        if (*stri1 != *stri2)
            return (*stri1 - *stri2);
        stri1++;
        stri2++;
    }
    if (*stri1 == *stri2)
        return (0);
    else
        return (*stri1 < *stri2 ? -1 : 1);
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * custom_starts_with - checks if substring starts with the main string
 * @main_stri: string to search
 * @sub_stri: the substring to find
 * starts_with_sub - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of the next character of main_stri or NULL
 * Return: address of next char of haystack or NULL
 */
char *custom_starts_with(const char *main_stri, const char *sub_stri)
char *starts_with_sub(const char *haystack, const char *needle)
{
    while (*sub_stri)
        if (*sub_stri++ != *main_stri++)
            return (NULL);
    return ((char *)main_stri);
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * custom_strcat - concatenates two strings
 * _strct - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to the destination buffer
 * Return: pointer to destination buffer
 */
char *custom_strcat(char *dest, char *src)
char *_strct(char *dest, char *src)
{
    char *ret = dest;
	char *ret = dest;

    while (*dest)
        dest++;
    while (*src)
        *dest++ = *src++;
    *dest = *src;
    return ret;
	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

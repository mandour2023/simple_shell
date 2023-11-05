#include "shell.h"

/**
 * custom_strlen - returns the length of a string
 * @stri: the string whose length to check
 *
 * Return: integer length of string
 */
int custom_strlen(char *stri)
{
    int length = 0;

    if (!stri)
        return (0);

    while (*stri++)
        length++;
    return length;
}
/**
 * custom_strcmp - performs lexicographic comparison of two strings.
 * @stri1: the first string
 * @stri2: the second string
 *
 * Return: negative if stri1 < stri2, positive if stri1 > stri2, zero if stri1 == stri2
 */
int custom_strcmp(char *stri1, char *stri2)
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
}

/**
 * custom_starts_with - checks if substring starts with the main string
 * @main_stri: string to search
 * @sub_stri: the substring to find
 *
 * Return: address of the next character of main_stri or NULL
 */
char *custom_starts_with(const char *main_stri, const char *sub_stri)
{
    while (*sub_stri)
        if (*sub_stri++ != *main_stri++)
            return (NULL);
    return ((char *)main_stri);
}
/**
 * custom_strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to the destination buffer
 */
char *custom_strcat(char *dest, char *src)
{
    char *ret = dest;

    while (*dest)
        dest++;
    while (*src)
        *dest++ = *src++;
    *dest = *src;
    return ret;
}

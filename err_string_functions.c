#include "shell.h"

/**
 * _epstr - prints an input string
 * @s: the string to be printed
 *
 * Return: Nothing
 */
void _epstr(char *s)
{
	int i = 0;

	if (!s)
		return;
	while (s[i] != '\0')
	{
		_ech(s[i]);
		i++;
	}
}

/**
 * _ech - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _ech(char c)
{
	static int i;
	static char b[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, b, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		b[i++] = c;
	return (1);
}

/**
 * _pfd - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _pfd(char c, int fd)
{
	static int i;
	static char b[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, b, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		b[i++] = c;
	return (1);
}

/**
 * _pstrfd - prints an input string
 * @s: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _pstrfd(char *s, int fd)
{
	int i = 0;

	if (!s)
		return (0);
	while (*s)
	{
		i += _pfd(*s++, fd);
	}
	return (i);
}

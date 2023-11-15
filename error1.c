#include "shell.h"

/**
 * _xtoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _xtoi(char *s)
{
	int i = 0;
	unsigned long int r = 0;

	if (*s == '+')
		s++;
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			r *= 10;
			r += (s[i] - '0');
			if (r > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (r);
}

/**
 * p_err - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void p_err(info_t *info, char *estr)
{
	_ep(info->fname);
	_ep(": ");
	p_d(info->line_count, STDERR_FILENO);
	_ep(": ");
	_ep(info->argv[0]);
	_ep(": ");
	_ep(estr);
}

/**
 * p_d - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int p_d(int input, int fd)
{
	int (*__pchar)(char) = _pchar;
	int i, count = 0;
	unsigned int a, c;

	if (fd == STDERR_FILENO)
		__pchar = _epchar;
	if (input < 0)
	{
		a = -input;
		__pchar('-');
		count++;
	}
	else
		a = input;
	c = a;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (a / i)
		{
			__pchar('0' + c / i);
			count++;
		}
		c %= i;
	}
	__pchar('0' + c);
	count++;

	return (count);
}

/**
 * c_num - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *c_num(long int num, int base, int flags)
{
	static char *arr;
	static char buff[50];
	char s = 0;
	char *p;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		s = '-';

	}
	arr = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &buff[49];
	*p = '\0';

	do	{
		*--p = arr[n % base];
		n /= base;
	} while (n != 0);

	if (s)
		*--p = s;
	return (p);
}

/**
 * rem_com - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void rem_com(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}

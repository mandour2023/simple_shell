#include "shell.h"
/**
 * checkInteractive - returns true if shell is in interactive mode
 * @infoData: struct address
 *
 * Return: 1 if in interactive mode, 0 otherwise
 */
int checkInteractive(info_t *infoData)
{
	return (isatty(STDIN_FILENO) && infoData->readfd <= 2);
}
/**
 * isDelimiter - checks if character is a delimiter
 * @c: the character to check
 * @delimiter: the delimiter string
 * Return: 1 if true, 0 if false
 */
int isDelimiter(char c, char *delimiter)
{
	while (*delimiter)
		if (*delimiter++ == c)
			return (1);
	return (0);
}
/**
 * isAlphabetic - checks for alphabetic character
 * @c: The character to check
 * Return: 1 if c is alphabetic, 0 otherwise
 */
int isAlphabetic(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * stringToInteger - converts a string to an integer
 * @str: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */
int stringToInteger(char *str)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; str[i] != '\0' && flag != 2; i++)
	{
		if (str[i] == '-')
			sign *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}


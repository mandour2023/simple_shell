#include "shell.h"

/**
 * _xexit - exits the shell
 * @i: Structure containing potential arguments. Used to maintain
 *      constant function prototype.
 * Return: exits with a given exit status
 *         (0) if i->args[0] != "exit"
 */
int _xexit(info_t *i)
{
	int xcheck;

	if (i->args[1])  /* If there is an exit argument */
	{
		xcheck = _erratoi(i->args[1]);
		if (xcheck == -1)
		{
			i->status = 2;
			print_error(i, "Illegal number: ");
			_eputs(i->args[1]);
			_eputchar('\n');
			return (1);
		}
		i->err_num = _erratoi(i->args[1]);
		return (-2);
	}
	i->err_num = -1;
	return (-2);
}

/**
 * _xcd - changes the current directory of the process
 * @i: Structure containing potential arguments. Used to maintain
 *      constant function prototype.
 * Return: Always 0
 */
int _xcd(info_t *i)
{
	char *s, *dir, buffer[1024];
	int r;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!i->args[1])
	{
		dir = _getenv(i, "HOME=");
		if (!dir)
			r = /* TODO: what should this be? */
				chdir((dir = _getenv(i, "PWD=")) ? dir : "/");
		else
			r = chdir(dir);
	}
	else if (_strcmp(i->args[1], "-") == 0)
	{
		if (!_getenv(i, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(i, "OLDPWD=")), _putchar('\n');
		r = /* TODO: what should this be? */
			chdir((dir = _getenv(i, "OLDPWD=")) ? dir : "/");
	}
	else
		r = chdir(i->args[1]);
	if (r == -1)
	{
		print_error(i, "can't cd to ");
		_eputs(i->args[1]), _eputchar('\n');
	}
	else
	{
		_setenv(i, "OLDPWD", _getenv(i, "PWD="));
		_setenv(i, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _xhelp - changes the current directory of the process
 * @i: Structure containing potential arguments. Used to maintain
 *      constant function prototype.
 * Return: Always 0
 */
int _xhelp(info_t *i)
{
	char **a_array;

	a_array = i->args;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*a_array); /* temp att_unused workaround */
	return (0);
}

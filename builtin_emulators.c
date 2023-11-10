#include "custom_shell.h"

/**
 * custom_exit - exits the shell
 * @data: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if data.arg_list[0] != "exit"
 */
int custom_exit(custom_data_t *data)
{
	int exit_check;

	if (data->arg_list[1])  /* If there is an exit argument */
	{
		exit_check = custom_atoi(data->arg_list[1]);
		if (exit_check == -1)
		{
			data->status = 2;
			print_error(data, "Illegal number: ");
			_eputs(data->arg_list[1]);
			_eputchar('\n');
			return (1);
		}
		data->error_number = custom_atoi(data->arg_list[1]);
		return (-2);
	}
	data->error_number = -1;
	return (-2);
}

/**
 * custom_change_directory - changes the current directory of the process
 * @data: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int custom_change_directory(custom_data_t *data)
{
	char *current_dir, *directory, buffer[1024];
	int chdir_result;

	current_dir = getcwd(buffer, 1024);
	if (!current_dir)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!data->arg_list[1])
	{
		directory = _getenv(data, "HOME=");
		if (!directory)
			chdir_result = /* TODO: what should this be? */
				chdir((directory = _getenv(data, "PWD=")) ? directory : "/");
		else
			chdir_result = chdir(directory);
	}
	else if (_strcmp(data->arg_list[1], "-") == 0)
	{
		if (!_getenv(data, "OLDPWD="))
		{
			_puts(current_dir);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(data, "OLDPWD=")), _putchar('\n');
		chdir_result = /* TODO: what should this be? */
			chdir((directory = _getenv(data, "OLDPWD=")) ? directory : "/");
	}
	else
		chdir_result = chdir(data->arg_list[1]);
	if (chdir_result == -1)
	{
		print_error(data, "can't cd to ");
		_eputs(data->arg_list[1]), _eputchar('\n');
	}
	else
	{
		_setenv(data, "OLDPWD", _getenv(data, "PWD="));
		_setenv(data, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * custom_help - displays help information
 * @data: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int custom_help(custom_data_t *data)
{
	char **arg_array;

	arg_array = data->arg_list;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}

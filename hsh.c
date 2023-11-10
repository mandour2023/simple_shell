#include "custom_shell.h"

/**
 * custom_shell_loop - main shell loop
 * @data: the parameter & return data struct
 * @arguments: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int custom_shell_loop(custom_data_t *data, char **arguments)
{
	ssize_t input_length = 0;
	int builtin_result = 0;

	while (input_length != -1 && builtin_result != -2)
	{
		clear_data(data);
		if (is_interactive(data))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		input_length = get_user_input(data);
		if (input_length != -1)
		{
			set_data(data, arguments);
			builtin_result = find_builtin_command(data);
			if (builtin_result == -1)
				find_custom_command(data);
		}
		else if (is_interactive(data))
			_putchar('\n');
		free_data(data, 0);
	}
	write_history(data);
	free_data(data, 1);
	if (!is_interactive(data) && data->status)
		exit(data->status);
	if (builtin_result == -2)
	{
		if (data->error_number == -1)
			exit(data->status);
		exit(data->error_number);
	}
	return (builtin_result);
}

/**
 * find_builtin_command - finds a builtin command
 * @data: the parameter & return data struct
 *
 * Return: -1 if builtin not found,
 *         0 if builtin executed successfully,
 *         1 if builtin found but not successful,
 *         -2 if builtin signals exit()
 */
int find_builtin_command(custom_data_t *data)
{
	int i, builtin_result = -1;
	builtin_table custom_builtins[] = {
		{"exit", custom_exit},
		{"env", custom_env},
		{"help", custom_help},
		{"history", custom_history},
		{"setenv", custom_setenv},
		{"unsetenv", custom_unsetenv},
		{"cd", custom_cd},
		{"alias", custom_alias},
		{NULL, NULL}
	};

	for (i = 0; custom_builtins[i].type; i++)
		if (_strcmp(data->arg[0], custom_builtins[i].type) == 0)
		{
			data->line_count++;
			builtin_result = custom_builtins[i].function(data);
			break;
		}
	return (builtin_result);
}

/**
 * find_custom_command - finds a command in PATH
 * @data: the parameter & return data struct
 *
 * Return: void
 */
void find_custom_command(custom_data_t *data)
{
	char *path = NULL;
	int i, argument_count;

	data->path = data->arg[0];
	if (data->line_count_flag == 1)
	{
		data->line_count++;
		data->line_count_flag = 0;
	}
	for (i = 0, argument_count = 0; data->arguments[i]; i++)
		if (!is_delimiter(data->arguments[i], " \t\n"))
			argument_count++;
	if (!argument_count)
		return;

	path = find_path(data, _getenv(data, "PATH="), data->arg[0]);
	if (path)
	{
		data->path = path;
		fork_custom_command(data);
	}
	else
	{
		if ((is_interactive(data) || _getenv(data, "PATH=")
			|| data->arg[0][0] == '/') && is_command(data, data->arg[0]))
			fork_custom_command(data);
		else if (*(data->arg) != '\n')
		{
			data->status = 127;
			print_error(data, "not found\n");
		}
	}
}

/**
 * fork_custom_command - forks an exec thread to run cmd
 * @data: the parameter & return data struct
 *
 * Return: void
 */
void fork_custom_command(custom_data_t *data)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(data->path, data->arg, get_environment(data)) == -1)
		{
			free_data(data, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(data->status));
		if (WIFEXITED(data->status))
		{
			data->status = WEXITSTATUS(data->status);
			if (data->status == 126)
				print_error(data, "Permission denied\n");
		}
	}
}

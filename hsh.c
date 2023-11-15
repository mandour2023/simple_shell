#include "shell.h"

/**
 * hsh_table - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh_table(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		reupdate_info(info);
		if (interface(info))
			_view("$ ");
		_ech(BUF_FLUSH);
		r = retrieve_input(info);
		if (r != -1)
		{
			update_info(info, av);
			builtin_ret = search_builtin(info);
			if (builtin_ret == -1)
				search_command(info);
		}
		else if (interface(info))
			_output('\n');
		release_info(info, 0);
	}
	save_history(info);
	release_info(info, 1);
	if (!interface(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * search_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int search_builtin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcomp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * search_command - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void search_command(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_sep(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = locate_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		execute_command(info);
	}
	else
	{
		if ((interface(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && check_cmd(info, info->argv[0]))
			execute_command(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			display_err(info, "not found\n");
		}
	}
}

/**
 * execute_command - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void execute_command(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			release_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				display_err(info, "Permission denied\n");
		}
	}
}

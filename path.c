#include "custom_shell.h"

/**
 * is_command - determines if a file is an executable command
 * @data: the custom_data_t struct
 * @file_path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_command(custom_data_t *data, char *file_path)
{
	struct stat file_stat;

	(void)data;
	if (!file_path || stat(file_path, &file_stat))
		return (0);

	if (file_stat.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplicate_characters - duplicates characters
 * @path_string: the PATH string
 * @start_index: starting index
 * @stop_index: stopping index
 *
 * Return: pointer to new buffer
 */
char *duplicate_characters(char *path_string, int start_index, int stop_index)
{
	static char buffer[1024];
	int i = 0, k = 0;

	for (k = 0, i = start_index; i < stop_index; i++)
		if (path_string[i] != ':')
			buffer[k++] = path_string[i];
	buffer[k] = 0;
	return (buffer);
}

/**
 * find_command_path - finds this command in the PATH string
 * @data: the custom_data_t struct
 * @path_string: the PATH string
 * @command: the command to find
 *
 * Return: full path of command if found or NULL
 */
char *find_command_path(custom_data_t *data, char *path_string, char *command)
{
	int i = 0, current_pos = 0;
	char *path;

	if (!path_string)
		return (NULL);
	if ((_strlen(command) > 2) && starts_with(command, "./"))
	{
		if (is_command(data, command))
			return (command);
	}
	while (1)
	{
		if (!path_string[i] || path_string[i] == ':')
		{
			path = duplicate_characters(path_string, current_pos, i);
			if (!*path)
				_strcat(path, command);
			else
			{
				_strcat(path, "/");
				_strcat(path, command);
			}
			if (is_command(data, path))
				return (path);
			if (!path_string[i])
				break;
			current_pos = i;
		}
		i++;
	}
	return (NULL);
}

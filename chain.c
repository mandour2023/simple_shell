#include "custom_shell.h"

/**
 * is_command_separator - tests if the current character in the buffer is a command separator
 * @data: the parameter struct
 * @buffer: the char buffer
 * @position: address of the current position in buffer
 *
 * Return: 1 if command separator, 0 otherwise
 */
int is_command_separator(custom_data_t *data, char *buffer, size_t *position)
{
	size_t j = *position;

	if (buffer[j] == '|' && buffer[j + 1] == '|')
	{
		buffer[j] = 0;
		j++;
		data->command_buffer_type = CMD_OR;
	}
	else if (buffer[j] == '&' && buffer[j + 1] == '&')
	{
		buffer[j] = 0;
		j++;
		data->command_buffer_type = CMD_AND;
	}
	else if (buffer[j] == ';') /* found end of this command */
	{
		buffer[j] = 0; /* replace semicolon with null */
		data->command_buffer_type = CMD_CHAIN;
	}
	else
		return (0);
	*position = j;
	return (1);
}

/**
 * check_command_chain - checks if we should continue chaining based on the last status
 * @data: the parameter struct
 * @buffer: the char buffer
 * @position: address of the current position in buffer
 * @start_position: starting position in buffer
 * @length: length of buffer
 *
 * Return: Void
 */
void check_command_chain(custom_data_t *data, char *buffer, size_t *position, size_t start_position, size_t length)
{
	size_t j = *position;

	if (data->command_buffer_type == CMD_AND)
	{
		if (data->status)
		{
			buffer[start_position] = 0;
			j = length;
		}
	}
	if (data->command_buffer_type == CMD_OR)
	{
		if (!data->status)
		{
			buffer[start_position] = 0;
			j = length;
		}
	}

	*position = j;
}

/**
 * replace_command_alias - replaces an alias in the tokenized string
 * @data: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_command_alias(custom_data_t *data)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(data->alias_list, data->arg_list[0], '=');
		if (!node)
			return (0);
		free(data->arg_list[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		data->arg_list[0] = p;
	}
	return (1);
}

/**
 * replace_command_variables - replaces variables in the tokenized string
 * @data: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_command_variables(custom_data_t *data)
{
	int i = 0;
	list_t *node;

	for (i = 0; data->arg_list[i]; i++)
	{
		if (data->arg_list[i][0] != '$' || !data->arg_list[i][1])
			continue;

		if (!_strcmp(data->arg_list[i], "$?"))
		{
			replace_string(&(data->arg_list[i]),
				_strdup(convert_number(data->status, 10, 0)));
			continue;
		}
		if (!_strcmp(data->arg_list[i], "$$"))
		{
			replace_string(&(data->arg_list[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(data->environment, &data->arg_list[i][1], '=');
		if (node)
		{
			replace_string(&(data->arg_list[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&data->arg_list[i], _strdup(""));
	}
	return (0);
}

/**
 * replace_string_content - replaces string content
 * @old_content: address of the old string content
 * @new_content: new string content
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string_content(char **old_content, char *new_content)
{
	free(*old_content);
	*old_content = new_content;
	return (1);
}

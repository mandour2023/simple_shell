#include "custom_shell.h"

/**
 * fetch_environment - returns the string array copy of our environment
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
char **fetch_environment(custom_data_t *data)
{
	if (!data->environment || data->environment_changed)
	{
		data->environment = list_to_strings(data->env_list);
		data->environment_changed = 0;
	}

	return (data->environment);
}

/**
 * discard_environment_var - Remove an environment variable
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @variable: the string env variable property
 * Return: 1 on delete, 0 otherwise
 */
int discard_environment_var(custom_data_t *data, char *variable)
{
	list_t *node = data->env_list;
	size_t index = 0;
	char *p;

	if (!node || !variable)
		return (0);

	while (node)
	{
		p = starts_with(node->str, variable);
		if (p && *p == '=')
		{
			data->environment_changed = delete_node_at_index(&(data->env_list), index);
			index = 0;
			node = data->env_list;
			continue;
		}
		node = node->next;
		index++;
	}
	return (data->environment_changed);
}

/**
 * set_environment_var - Initialize a new environment variable,
 *                       or modify an existing one
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @variable: the string env variable property
 * @value: the string env variable value
 * Return: Always 0
 */
int set_environment_var(custom_data_t *data, char *variable, char *value)
{
	char *buffer = NULL;
	list_t *node;
	char *p;

	if (!variable || !value)
		return (0);

	buffer = malloc(_strlen(variable) + _strlen(value) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, variable);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	node = data->env_list;
	while (node)
	{
		p = starts_with(node->str, variable);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buffer;
			data->environment_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(data->env_list), buffer, 0);
	free(buffer);
	data->environment_changed = 1;
	return (0);
}

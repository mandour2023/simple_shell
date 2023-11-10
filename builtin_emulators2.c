#include "custom_shell.h"

/**
 * custom_history - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int custom_history(custom_data_t *data)
{
	print_list(data->command_history);
	return (0);
}

/**
 * remove_alias - removes alias by string
 * @data: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int remove_alias(custom_data_t *data, char *str)
{
	char *p, c;
	int result;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	result = delete_node_at_index(&(data->alias_list),
		get_node_index(data->alias_list, node_starts_with(data->alias_list, str, -1)));
	*p = c;
	return (result);
}

/**
 * set_alias_custom - sets alias to string
 * @data: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias_custom(custom_data_t *data, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (remove_alias(data, str));

	remove_alias(data, str);
	return (add_node_end(&(data->alias_list), str, 0) == NULL);
}

/**
 * display_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int display_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * custom_alias - mimics the alias builtin (man alias)
 * @data: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int custom_alias(custom_data_t *data)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (data->arg_count == 1)
	{
		node = data->alias_list;
		while (node)
		{
			display_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; data->arg_list[i]; i++)
	{
		p = _strchr(data->arg_list[i], '=');
		if (p)
			set_alias_custom(data, data->arg_list[i]);
		else
			display_alias(node_starts_with(data->alias_list, data->arg_list[i], '='));
	}

	return (0);
}

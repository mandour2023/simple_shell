#include "shell.h"

/**
 * _myenv - prints the current environment
 * @p: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myenv(info_t *p)
{
	print_list_str(p->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @p: Structure containing potential arguments. Used to maintain
 * @n: env var name
 *
 * Return: the value
 */
char *_getenv(info_t *p, const char *n)
{
	list_t *n_ptr = p->env;
	char *s;

	while (n_ptr)
	{
		s = starts_with(n_ptr->str, n);
		if (s && *s)
			return (s);
		n_ptr = n_ptr->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @p: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _mysetenv(info_t *p)
{
	if (p->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(p, p->argv[1], p->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove an environment variable
 * @p: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myunsetenv(info_t *p)
{
	int i;

	if (p->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= p->argc; i++)
		_unsetenv(p, p->argv[i]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @p: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *p)
{
	list_t *n_ptr = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&n_ptr, environ[i], 0);
	p->env = n_ptr;
	return (0);
}

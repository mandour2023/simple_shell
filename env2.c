#include "shell.h"

/**
 * a - returns the string array copy of our environ
 * @b: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **a(b *b)
{
	if (!b->environ || b->env_changed)
	{
		b->environ = list_to_strings(b->env);
		b->env_changed = 0;
	}

	return (b->environ);
}

/**
 * c - Remove an environment variable
 * @b: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @d: the string env var property
 */
int c(b *b, char *d)
{
	list_t *e = b->env;
	size_t f = 0;
	char *g;

	if (!e || !d)
		return (0);

	while (e)
	{
		g = starts_with(e->str, d);
		if (g && *g == '=')
		{
			b->env_changed = delete_node_at_index(&(b->env), f);
			f = 0;
			e = b->env;
			continue;
		}
		e = e->next;
		f++;
	}
	return (b->env_changed);
}

/**
 * h - Initialize a new environment variable,
 *             or modify an existing one
 * @b: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @d: the string env var property
 * @i: the string env var value
 *  Return: Always 0
 */
int h(b *b, char *d, char *i)
{
	char *j = NULL;
	list_t *k;
	char *l;

	if (!d || !i)
		return (0);

	j = malloc(_strlen(d) + _strlen(i) + 2);
	if (!j)
		return (1);
	_strcpy(j, d);
	_strcat(j, "=");
	_strcat(j, i);
	k = b->env;
	while (k)
	{
		l = starts_with(k->str, d);
		if (l && *l == '=')
		{
			free(k->str);
			k->str = j;
			b->env_changed = 1;
			return (0);
		}
		k = k->next;
	}
	add_node_end(&(b->env), j, 0);
	free(j);
	b->env_changed = 1;
	return (0);
}

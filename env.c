#include "shell.h"

/**
 * _myctx - prints the current environment
 * @ctx: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int _myctx(ctx_t *ctx)
{
	print_list_str(ctx->env);
	return (0);
}

/**
 * _myvalue - gets the value of an environ variable
 * @ctx: Structure containing potential arguments. Used to maintain
 * @key: env var name
 *
 * Return: the value
 */
char *_myvalue(ctx_t *ctx, const char *key)
{
	list_t *node = ctx->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, key);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetup - Initialize a new environment variable,
 *             or modify an existing one
 * @ctx: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int _mysetup(ctx_t *ctx)
{
	if (ctx->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(ctx, ctx->argv[1], ctx->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunset - Remove an environment variable
 * @ctx: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int _myunset(ctx_t *ctx)
{
	int i;

	if (ctx->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= ctx->argc; i++)
		_unsetenv(ctx, ctx->argv[i]);

	return (0);
}

/**
 * _populate - populates env linked list
 * @ctx: Structure containing potential arguments. Used to maintain
 *            constant function prototype.
 * Return: Always 0
 */
int _populate(ctx_t *ctx)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	ctx->env = node;
	return (0);
}

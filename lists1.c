#include "shell.h"

/**
 * len_list - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t len_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * list_to_strs - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strs(list_t *head)
{
	list_t *nd = head;
	size_t i = len_list(head), j;
	char **strs;
	char *s;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; nd; nd = nd->next, i++)
	{
		s = malloc(_strlen(nd->str) + 1);
		if (!s)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		s = _strcpy(s, nd->str);
		strs[i] = s;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * print_lst_all - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_lst_all(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(conv_num(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * nd_starts_with - returns node whose string starts with prefix
 * @nd: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *nd_starts_with(list_t *nd, char *prefix, char c)
{
	char *p = NULL;

	while (nd)
	{
		p = starts_with(nd->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (nd);
		nd = nd->next;
	}
	return (NULL);
}

/**
 * get_nd_index - gets the index of a node
 * @head: pointer to list head
 * @nd: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_nd_index(list_t *head, list_t *nd)
{
	size_t i = 0;

	while (head)
	{
		if (head == nd)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}

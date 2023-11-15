#include "shell.h"

/**
 * add_nd - adds a node to the start of the list
 * @hd: address of pointer to head node
 * @s: str field of node
 * @n: node index used by history
 *
 * Return: size of list
 */
list_t *add_nd(list_t **hd, const char *s, int n)
{
	list_t *new_hd;

	if (!hd)
		return (NULL);
	new_hd = malloc(sizeof(list_t));
	if (!new_hd)
		return (NULL);
	_memset((void *)new_hd, 0, sizeof(list_t));
	new_hd->num = n;
	if (s)
	{
		new_hd->str = _strdup(s);
		if (!new_hd->str)
		{
			free(new_hd);
			return (NULL);
		}
	}
	new_hd->next = *hd;
	*hd = new_hd;
	return (new_hd);
}

/**
 * add_nd_end - adds a node to the end of the list
 * @hd: address of pointer to head node
 * @s: str field of node
 * @n: node index used by history
 *
 * Return: size of list
 */
list_t *add_nd_end(list_t **hd, const char *s, int n)
{
	list_t *new_nd, *nd;

	if (!hd)
		return (NULL);

	nd = *hd;
	new_nd = malloc(sizeof(list_t));
	if (!new_nd)
		return (NULL);
	_memset((void *)new_nd, 0, sizeof(list_t));
	new_nd->num = n;
	if (s)
	{
		new_nd->str = _strdup(s);
		if (!new_nd->str)
		{
			free(new_nd);
			return (NULL);
		}
	}
	if (nd)
	{
		while (nd->next)
			nd = nd->next;
		nd->next = new_nd;
	}
	else
		*hd = new_nd;
	return (new_nd);
}

/**
 * print_lst_s - prints only the str element of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_lst_s(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * del_nd_at_ind - deletes node at given index
 * @hd: address of pointer to first node
 * @ind: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int del_nd_at_ind(list_t **hd, unsigned int ind)
{
	list_t *nd, *prev_nd;
	unsigned int i = 0;

	if (!hd || !*hd)
		return (0);

	if (!ind)
	{
		nd = *hd;
		*hd = (*hd)->next;
		free(nd->str);
		free(nd);
		return (1);
	}
	nd = *hd;
	while (nd)
	{
		if (i == ind)
		{
			prev_nd->next = nd->next;
			free(nd->str);
			free(nd);
			return (1);
		}
		i++;
		prev_nd = nd;
		nd = nd->next;
	}
	return (0);
}

/**
 * free_lst - frees all nodes of a list
 * @hd_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_lst(list_t **hd_ptr)
{
	list_t *nd, *nxt_nd, *hd;

	if (!hd_ptr || !*hd_ptr)
		return;
	hd = *hd_ptr;
	nd = hd;
	while (nd)
	{
		nxt_nd = nd->next;
		free(nd->str);
		free(nd);
		nd = nxt_nd;
	}
	*hd_ptr = NULL;
}

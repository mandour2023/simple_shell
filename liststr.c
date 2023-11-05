#include "my_shell.h"

/**
 * add_list_node - adds a node to the start of the list
 * @head_ptr: address of pointer to head node
 * @data: data field of the node
 * @index: node index used by history
 *
 * Return: size of list
 */
list_t *add_list_node(list_t **head_ptr, const char *data, int index)
{
	list_t *new_node;

	if (!head_ptr)
		return (NULL);
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_initialize_node((void *)new_node, 0, sizeof(list_t));
	new_node->index = index;
	if (data)
	{
		new_node->data = _str_duplicate(data);
		if (!new_node->data)
		{
			free(new_node);
			return (NULL);
		}
	}
	new_node->next = *head_ptr;
	*head_ptr = new_node;
	return (new_node);
}

/**
 * add_list_node_end - adds a node to the end of the list
 * @head_ptr: address of pointer to head node
 * @data: data field of the node
 * @index: node index used by history
 *
 * Return: size of list
 */
list_t *add_list_node_end(list_t **head_ptr, const char *data, int index)
{
	list_t *new_node, *node;

	if (!head_ptr)
		return (NULL);

	node = *head_ptr;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_initialize_node((void *)new_node, 0, sizeof(list_t));
	new_node->index = index;
	if (data)
	{
		new_node->data = _str_duplicate(data);
		if (!new_node->data)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head_ptr = new_node;
	return (new_node);
}

/**
 * print_data_list - prints only the data element of a list_t linked list
 * @node: pointer to first node
 *
 * Return: size of list
 */
size_t print_data_list(const list_t *node)
{
	size_t i = 0;

	while (node)
	{
		_print_string(node->data ? node->data : "(nil)");
		_print_string("\n");
		node = node->next;
		i++;
	}
	return (i);
}

/**
 * delete_node_at_index - deletes node at given index
 * @head_ptr: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head_ptr, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head_ptr || !*head_ptr)
		return (0);

	if (!index)
	{
		node = *head_ptr;
		*head_ptr = (*head_ptr)->next;
		free(node->data);
		free(node);
		return (1);
	}
	node = *head_ptr;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->data);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_data_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_data_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->data);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}

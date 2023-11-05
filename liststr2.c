#include "shell.h"

/**
 * count_elements - determines the number of elements in the linked list
 * @h: pointer to the first node
 *
 * Return: number of elements
 */
size_t count_elements(const list_t *h)
{
    size_t count = 0;

    while (h)
    {
        h = h->next;
        count++;
    }
    return count;
}

/**
 * list_to_strings - converts the list of strings into an array of strings
 * @head: pointer to the first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
    list_t *node = head;
    size_t num_elements = count_elements(head), index;
    char **string_array;
    char *str;

    if (!head || !num_elements)
        return NULL;
    string_array = malloc(sizeof(char *) * (num_elements + 1));
    if (!string_array)
        return NULL;
    for (index = 0; node; node = node->next, index++)
    {
        str = malloc(_string_length(node->str) + 1);
        if (!str)
        {
            for (size_t j = 0; j < index; j++)
                free(string_array[j]);
            free(string_array);
            return NULL;
        }

        str = _copy_string(str, node->str);
        string_array[index] = str;
    }
    string_array[index] = NULL;
    return string_array;
}

/**
 * print_list - prints all elements of a list_t linked list
 * @h: pointer to the first node
 *
 * Return: number of elements
 */
size_t print_list(const list_t *h)
{
    size_t count = 0;

    while (h)
    {
        _put_string(convert_number(h->num, 10, NULL);  // Replaced 0 with NULL
        _put_char(':');
        _put_char(' ');
        _put_string(h->str ? h->str : "(nil)");
        _put_string("\n");
        h = h->next;
        count++;
    }
    return count;
}
/**
 * find_node_with_prefix - returns a node whose string starts with a given prefix
 * @node: pointer to the list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: matching node or NULL
 */
list_t *find_node_with_prefix(list_t *node, char *prefix, char c)
{
    char *str = NULL;

    while (node)
    {
        str = starts_with(node->str, prefix);
        if (str && ((c == -1) || (*str == c)))
            return node;
        node = node->next;
    }
    return NULL;
}
/**
 * get_node_index - gets the index of a node in the list
 * @head: pointer to the list head
 * @node: pointer to the node
 *
 * Return: index of the node or -1 if not found
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
    size_t index = 0;

    while (head)
    {
        if (head == node)
            return index;
        head = head->next;
        index++;
    }
    return -1;
}


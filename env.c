#include "custom_shell.h"

/**
 * display_custom_environment - prints the current custom environment
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int display_custom_environment(custom_data_t *data)
{
    print_string_list(data->environment);
    return (0);
}

/**
 * get_custom_environment_value - gets the value of a custom environment variable
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @name: custom environment variable name
 *
 * Return: the value
 */
char *get_custom_environment_value(custom_data_t *data, const char *name)
{
    list_t *node = data->environment;
    char *value;

    while (node)
    {
        value = starts_with(node->str, name);
        if (value && *value)
            return value;
        node = node->next;
    }
    return NULL;
}

/**
 * set_custom_environment - Initialize a new custom environment variable,
 *                         or modify an existing one
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int set_custom_environment(custom_data_t *data)
{
    if (data->arg_count != 3)
    {
        print_error("Incorrect number of arguments\n");
        return 1;
    }
    if (set_environment_variable(data, data->arg_list[1], data->arg_list[2]))
        return 0;
    return 1;
}

/**
 * unset_custom_environment - Remove a custom environment variable
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int unset_custom_environment(custom_data_t *data)
{
    int i;

    if (data->arg_count == 1)
    {
        print_error("Too few arguments.\n");
        return 1;
    }
    for (i = 1; i <= data->arg_count; i++)
        unset_environment_variable(data, data->arg_list[i]);

    return 0;
}

/**
 * populate_custom_environment_list - populates custom environment linked list
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int populate_custom_environment_list(custom_data_t *data)
{
    list_t *node = NULL;
    size_t i;

    for (i = 0; data->environment_variables[i]; i++)
        add_node_end(&node, data->environment_variables[i], 0);
    data->environment = node;
    return 0;
}

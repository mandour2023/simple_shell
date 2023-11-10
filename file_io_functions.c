#include "custom_shell.h"

/**
 * obtain_history_file - gets the history file
 * @data: parameter struct
 *
 * Return: allocated string containing history file
 */
char *obtain_history_file(custom_data_t *data)
{
    char *buffer, *directory;

    directory = _getenv(data, "HOME=");
    if (!directory)
        return (NULL);

    buffer = malloc(sizeof(char) * (_strlen(directory) + _strlen(CUSTOM_HIST_FILE) + 2));
    if (!buffer)
        return (NULL);

    buffer[0] = 0;
    _strcpy(buffer, directory);
    _strcat(buffer, "/");
    _strcat(buffer, CUSTOM_HIST_FILE);

    return buffer;
}

/**
 * record_history - creates a file, or appends to an existing file
 * @data: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int record_history(custom_data_t *data)
{
    ssize_t file_descriptor;
    char *filename = obtain_history_file(data);
    list_t *node = NULL;

    if (!filename)
        return (-1);

    file_descriptor = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(filename);

    if (file_descriptor == -1)
        return (-1);

    for (node = data->history; node; node = node->next)
    {
        _putsfd(node->str, file_descriptor);
        _putfd('\n', file_descriptor);
    }

    _putfd(BUF_FLUSH, file_descriptor);
    close(file_descriptor);

    return 1;
}

/**
 * read_history - reads history from file
 * @data: the parameter struct
 *
 * Return: hist_count on success, 0 otherwise
 */
int read_history(custom_data_t *data)
{
    int i, last = 0, line_count = 0;
    ssize_t file_descriptor, read_length, file_size = 0;
    struct stat file_stat;
    char *buffer = NULL, *filename = obtain_history_file(data);

    if (!filename)
        return 0;

    file_descriptor = open(filename, O_RDONLY);
    free(filename);

    if (file_descriptor == -1)
        return 0;

    if (!fstat(file_descriptor, &file_stat))
        file_size = file_stat.st_size;

    if (file_size < 2)
        return 0;

    buffer = malloc(sizeof(char) * (file_size + 1));

    if (!buffer)
        return 0;

    read_length = read(file_descriptor, buffer, file_size);
    buffer[file_size] = 0;

    if (read_length <= 0)
        return free(buffer), 0;

    close(file_descriptor);

    for (i = 0; i < file_size; i++)
        if (buffer[i] == '\n')
        {
            buffer[i] = 0;
            establish_history_list(data, buffer + last, line_count++);
            last = i + 1;
        }

    if (last != i)
        establish_history_list(data, buffer + last, line_count++);

    free(buffer);
    data->hist_count = line_count;

    while (data->hist_count-- >= CUSTOM_HIST_MAX)
        delete_node_at_index(&(data->history), 0);

    reorder_history(data);

    return data->hist_count;
}

/**
 * establish_history_list - adds entry to a history linked list
 * @data: Structure containing potential arguments. Used to maintain
 * @buffer: buffer
 * @line_count: the history line count, hist_count
 *
 * Return: Always 0
 */
int establish_history_list(custom_data_t *data, char *buffer, int line_count)
{
    list_t *node = NULL;

    if (data->history)
        node = data->history;

    add_node_end(&node, buffer, line_count);

    if (!data->history)
        data->history = node;

    return 0;
}

/**
 * reorder_history - renumbers the history linked list after changes
 * @data: Structure containing potential arguments. Used to maintain
 *
 * Return: the new hist_count
 */
int reorder_history(custom_data_t *data)
{
    list_t *node = data->history;
    int i = 0;

    while (node)
    {
        node->num = i++;
        node = node->next;
    }

    return (data->hist_count = i);
}

#include "custom_shell.h"

/**
 * buffer_commands - buffers chained commands
 * @data: parameter struct
 * @command_buffer: address of buffer
 * @buffer_length: address of buffer length var
 *
 * Return: bytes read
 */
ssize_t buffer_commands(custom_data_t *data, char **command_buffer, size_t *buffer_length)
{
	ssize_t bytes_read = 0;
	size_t buffer_position = 0;

	if (!*buffer_length) /* if nothing left in the buffer, fill it */
	{
		free(*command_buffer);
		*command_buffer = NULL;
		signal(SIGINT, interruptHandler);
#if USE_GETLINE
		bytes_read = getline(command_buffer, buffer_length, stdin);
#else
		bytes_read = _custom_getline(data, command_buffer, buffer_length);
#endif
		if (bytes_read > 0)
		{
			if ((*command_buffer)[bytes_read - 1] == '\n')
			{
				(*command_buffer)[bytes_read - 1] = '\0'; /* remove trailing newline */
				bytes_read--;
			}
			data->linecount_flag = 1;
			remove_comments(*command_buffer);
			build_history_list(data, *command_buffer, data->histcount++);
			{
				*buffer_length = bytes_read;
				data->cmd_buf = command_buffer;
			}
		}
	}
	return bytes_read;
}

/**
 * get_user_input - gets a line minus the newline
 * @data: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_user_input(custom_data_t *data)
{
	static char *command_buffer; /* the ';' command chain buffer */
	static size_t position_i, position_j, buffer_length;
	ssize_t bytes_read = 0;
	char **buffer_p = &(data->arg), *p;

	_putchar(BUF_FLUSH);
	bytes_read = buffer_commands(data, &command_buffer, &buffer_length);
	if (bytes_read == -1) /* EOF */
		return -1;
	if (buffer_length)	/* we have commands left in the chain buffer */
	{
		position_j = position_i; /* init new iterator to current buffer position */
		p = command_buffer + position_i; /* get pointer for return */

		check_command_chain(data, command_buffer, &position_j, position_i, buffer_length);
		while (position_j < buffer_length) /* iterate to semicolon or end */
		{
			if (is_command_separator(data, command_buffer, &position_j))
				break;
			position_j++;
		}

		position_i = position_j + 1; /* increment past nulled ';'' */
		if (position_i >= buffer_length) /* reached end of buffer? */
		{
			position_i = buffer_length = 0; /* reset position and length */
			data->command_buffer_type = CMD_NORM;
		}

		*buffer_p = p; /* pass back pointer to current command position */
		return _strlen(p); /* return length of current command */
	}

	*buffer_p = command_buffer; /* else not a chain, pass back buffer from _custom_getline() */
	return bytes_read; /* return length of buffer from _custom_getline() */
}

/**
 * read_buffer - reads a buffer
 * @data: parameter struct
 * @buffer: buffer
 * @buffer_size: size
 *
 * Return: r
 */
ssize_t read_buffer(custom_data_t *data, char *buffer, size_t *buffer_size)
{
	ssize_t bytes_read = 0;

	if (*buffer_size)
		return 0;
	bytes_read = read(data->readfd, buffer, READ_BUFFER_SIZE);
	if (bytes_read >= 0)
		*buffer_size = bytes_read;
	return bytes_read;
}

/**
 * _custom_getline - gets the next line of input from STDIN
 * @data: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _custom_getline(custom_data_t *data, char **ptr, size_t *length)
{
	static char buffer[READ_BUFFER_SIZE];
	static size_t position_i, buffer_length;
	size_t k;
	ssize_t bytes_read = 0, string_length = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		string_length = *length;
	if (position_i == buffer_length)
		position_i = buffer_length = 0;

	bytes_read = read_buffer(data, buffer, &buffer_length);
	if (bytes_read == -1 || (bytes_read == 0 && buffer_length == 0))
		return -1;

	c = _strchr(buffer + position_i, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : buffer_length;
	new_p = _realloc(p, string_length, string_length ? string_length + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (string_length)
		_strncat(new_p, buffer + position_i, k - position_i);
	else
		_strncpy(new_p, buffer + position_i, k - position_i + 1);

	string_length += k - position_i;
	position_i = k;
	p = new_p;

	if (length)
		*length = string_length;
	*ptr = p;
	return string_length;
}

/**
 * interruptHandler - blocks ctrl-C
 * @signal_num: the signal number
 *
 * Return: void
 */
void interruptHandler(__attribute__((unused))int signal_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

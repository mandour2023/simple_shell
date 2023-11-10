#include "custom_shell.h"

/**
 * reset_data - initializes custom_data_t struct
 * @data: struct address
 */
void reset_data(custom_data_t *data)
{
	data->arg = NULL;
	data->arg_list = NULL;
	data->path = NULL;
	data->arg_count = 0;
}

/**
 * initialize_data - initializes custom_data_t struct
 * @data: struct address
 * @arguments: argument vector
 */
void initialize_data(custom_data_t *data, char **arguments)
{
	int i = 0;

	data->program_name = arguments[0];
	if (data->arg)
	{
		data->arg_list = split_string(data->arg, " \t");
		if (!data->arg_list)
		{
			data->arg_list = malloc(sizeof(char *) * 2);
			if (data->arg_list)
			{
				data->arg_list[0] = duplicate_string(data->arg);
				data->arg_list[1] = NULL;
			}
		}
		for (i = 0; data->arg_list && data->arg_list[i]; i++)
			;
		data->arg_count = i;

		replace_alias(data);
		replace_variables(data);
	}
}

/**
 * release_data - frees custom_data_t struct fields
 * @data: struct address
 * @all: true if freeing all fields
 */
void release_data(custom_data_t *data, int all)
{
	free_string_array(data->arg_list);
	data->arg_list = NULL;
	data->path = NULL;
	if (all)
	{
		if (!data->command_buffer)
			free(data->arg);
		if (data->environment)
			free_list(&(data->environment));
		if (data->history)
			free_list(&(data->history));
		if (data->alias_list)
			free_list(&(data->alias_list));
		free_string_array(data->environment_variables);
		data->environment_variables = NULL;
		free_buffer((void **)data->command_buffer);
		if (data->read_file_descriptor > 2)
			close(data->read_file_descriptor);
		print_character(BUFFER_FLUSH);
	}
}

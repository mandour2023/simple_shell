#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* for convert_number() */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

extern char **custom_environment;

/**
 * struct custom_list_string - singly linked list
 * @number: the number field
 * @string: a string
 * @next: points to the next node
 */
typedef struct custom_list_string
{
    int number;
    char *string;
    struct custom_list_string *next;
} custom_list_t;

/**
 * struct custom_info - contains pseudo-arguments to pass into a function,
 *                    allowing a uniform prototype for the function pointer struct
 * @arguments: a string generated from getline containing arguments
 * @argument_vector: an array of strings generated from arguments
 * @custom_path: a string path for the current command
 * @argument_count: the argument count
 * @line_count: the error count
 * @error_number: the error code for exit()s
 * @linecount_flag: if on, count this line of input
 * @filename: the program filename
 * @custom_environment: linked list, a local copy of custom_environment
 * @history: the history node
 * @alias: the alias node
 * @environment_changed: on if custom_environment was changed
 * @status: the return status of the last exec'd command
 * @command_buffer: address of pointer to command_buffer, for memory management
 * @command_buffer_type: CMD_type ||, &&, ;
 * @read_file_descriptor: the file descriptor from which to read line input
 * @history_count: the history line number count
 */
typedef struct custom_info
{
    char *arguments;
    char **argument_vector;
    char *custom_path;
    int argument_count;
    unsigned int line_count;
    int error_number;
    int linecount_flag;
    char *filename;
    custom_list_t *custom_environment;
    custom_list_t *history;
    custom_list_t *alias;
    char **custom_environment;
    int environment_changed;
    int status;
    char **command_buffer; /* pointer to command ; chain buffer, for memory management */
    int command_buffer_type; /* CMD_type ||, &&, ; */
    int read_file_descriptor;
    int history_count;
} custom_info_t;

#define CUSTOM_INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, 0, 0, 0}

/**
 * struct custom_builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @function: the function
 */
typedef struct custom_builtin
{
    char *type;
    int (*function)(custom_info_t *);
} custom_builtin_table;

/* hsh.c */
int custom_shell(custom_info_t *, char **);
int find_custom_builtin(custom_info_t *);
void find_custom_command(custom_info_t *);
void fork_custom_command(custom_info_t *);

/* path.c */
int is_custom_command(custom_info_t *, char *);
char *duplicate_characters(char *, int, int);
char *find_custom_path(custom_info_t *, char *, char *);

/* loophsh.c */
int custom_loophsh(char **);

/* err_string_functions.c */
void custom_error_puts(char *);
int custom_error_putchar(char);
int custom_put_file_descriptor(char c, int file_descriptor);
int custom_puts_file_descriptor(char *str, int file_descriptor);

/* string_functions.c */
int custom_string_length(char *);
int custom_string_compare(char *, char *);
char *custom_starts_with(const char *, const char *);
char *custom_string_concatenate(char *, char *);

/* string_functions2.c */
char *custom_string_copy(char *, char *);
char *custom_string_duplicate(const char *);
void custom_puts_string(char *);
int custom_put_character(char);

/* string_functions3.c */
char *custom_string_copy_n(char *, char *, int);
char *custom_string_concatenate_n(char *, char *, int);
char *custom_string_character(char *, char);

/* string_functions4.c */
char **custom_string_split(char *, char *);
char **custom_string_split_n(char *, char);

/* memory_functions */
char *custom_memory_set(char *, char, unsigned int);
void custom_free(char **);
void *custom_reallocate(void *, unsigned int, unsigned int);

/* memory_functions2.c */
int custom_free(void **);

/* more_functions.c */
int custom_interactive(custom_info_t *);
int custom_is_delimiter(char, char *);
int custom_is_alpha(int);
int custom_integer_to_string(char *);

/* more_functions2.c */
int custom_error_integer_to_string(char *);
void print_error(custom_info_t *, char *);
int print_integer(int, int);
char *convert_integer(long int, int, int);
void remove_comments(char *);

/* builtin_emulators.c */
int custom_exit(custom_info_t *);
int custom_change_directory(custom_info_t *);
int custom_help(custom_info_t *);

/* builtin_emulators2.c */
int custom_history(custom_info_t *);
int custom_alias(custom_info_t *);

/* getline.c module */
ssize_t get_input(custom_info_t *);
int custom_getline(custom_info_t *, char **, size_t *);
void sigintHandler(int);

/* info.c module */
void clear_custom_info(custom_info_t *);
void set_custom_info(custom_info_t *, char **);
void free_custom_info(custom_info_t *, int);

/* env.c module */
char *get_custom_environment(custom_info_t *, const char *);
int custom_environment(custom_info_t *);
int custom_set_environment(custom_info_t *);
int custom_unset_environment(custom_info_t *);
int populate_custom_environment_list(custom_info_t *);

/* env2.c module */
char **get_custom_environment(custom_info_t *);
int custom_unset_environment(custom_info_t *, char *);
int custom_set_environment(custom_info_t *, char *, char *);

/* file_io_functions.c */
char *get_custom_history_file(custom_info_t *info);
int write_custom_history(custom_info_t *info);
int read_custom_history(custom_info_t *info);
int build_custom_history_list(custom_info_t *info, char *buffer, int history_count);
int renumber_custom_history(custom_info_t *info);

/* liststr.c module */
custom_list_t *add_node(custom_list_t **, const char *, int);
custom_list_t *add_node_end(custom_list_t **, const char *, int);
size_t print_list_string(const custom_list_t *);
int delete_node_at_index(custom_list_t **, unsigned int);
void free_list(custom_list_t **);

/* liststr2.c module */
size_t list_string_length(const custom_list_t *);
char **list_to_strings(custom_list_t *);
size_t print_list(const custom_list_t *);
custom_list_t *node_starts_with(custom_list_t *, char *, char);
ssize_t get_node_index(custom_list_t *, custom_list_t *);

/* chain.c */
int is_custom_chain(custom_info_t *, char *, size_t *);
void check_custom_chain(custom_info_t *, char *, size_t *, size_t, size_t);
int replace_alias(custom_info_t *);
int replace_custom_variables(custom_info_t *);
int replace_string(char **, char *);

#endif

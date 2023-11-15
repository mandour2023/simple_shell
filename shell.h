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
#define read_buffer_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for format_num() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system get_line() */
#define USE_get_line 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *					allowing uniform prototype for function pointer struct
 *@arg: a string generated from get_line containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* hsh_table.c */
int hsh_table(info_t *, char **);
int search_builtin(info_t *);
void search_command(info_t *);
void execute_command(info_t *);

/* path.c */
int check_cmd(info_t *, char *);
char *replicate(char *, int, int);
char *locate_path(info_t *, char *, char *);

/* loophsh_table.c */
int loophsh_table(char **);

/* err_string_functions.c */
void _epstr(char *);
int _ech(char);
int _pfd(char c, int fd);
int _pstrfd(char *str, int fd);

/* string_functions.c */
int _length(char *);
int _strcomp(char *, char *);
char *begins_with(const char *, const char *);
char *_strjoin(char *, char *);

/* string_functions2.c */
char *_cpystr(char *, char *);
char *_dupstr(const char *);
void _view(char *);
int _output(char);

/* string_functions3.c */
char *_strcat(char *, char *, int);
char *method(char *, char *, int);
char *_strstr(char *, char);

/* string_functions4.c */
char **strtow(char *, char *);
char **parse(char *, char);

/* memory_functions */
char *_set_memory(char *, char, unsigned int);
void deallocate(char **);
void *_realloc_(void *, unsigned int, unsigned int);

/* memory_functions2.c */
int bfr(void **);

/* more_functions.c */
int interface(info_t *);
int is_sep(char, char *);
int __isbeta(int);
int _btoi(char *);

/* more_functions2.c */
int _errtonum(char *);
void display_err(info_t *, char *);
int display_n(int, int);
char *format_num(long int, int, int);
void strip_comments(char *);

/* builtin_emulators.c */
int _xexit(info_t *);
int _xcd(info_t *);
int _xhelp(info_t *);

/* builtin_emulators2.c */
int _xhistory(info_t *);
int _xalias(info_t *);

/* get_line.c module */
ssize_t retrieve_input(info_t *);
int _get_line(info_t *, char **, size_t *);
void signal_interrupt_handler(int);

/* info.c module */
void reupdate_info(info_t *);
void update_info(info_t *, char **);
void release_info(info_t *, int);

/* env.c module */
char *_takeenv(info_t *, const char *);
int _xenv(info_t *);
int _xh(info_t *);
int _xc(info_t *);
int fill_env_list(info_t *);

/* env2.c module */
char **a(info_t *);
int _c(info_t *, char *);
int _h(info_t *, char *, char *);

/* file_io_functions.c */
char *retrieve_history_file(info_t *info);
int save_history(info_t *info);
int load_history(info_t *info);
int create_history_list(info_t *info, char *buf, int linecount);
int reorder_history(info_t *info);

/* liststr.c module */
list_t *insert_node(list_t **, const char *, int);
list_t *insert_node_end(list_t **, const char *, int);
size_t print_string_list(const list_t *);
int remove_node_at_index(list_t **, unsigned int);
void free_linked_list(list_t **);

/* liststr2.c module */
size_t length_of_list(const list_t *);
char **convert_list_strings(list_t *);
size_t display_list(const list_t *);
list_t *find_node_with(list_t *, char *, char);
ssize_t find_node_index(list_t *, list_t *);

/* chain.c */
int its_chain(info_t *, char *, size_t *);
void _check_chain(info_t *, char *, size_t *, size_t, size_t);
int x_replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif

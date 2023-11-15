#ifndef SHELL_H
#define SHELL_H

#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM    0
#define CMD_OR      1
#define CMD_AND     2
#define CMD_CHAIN   3

#define CONVERT_LOWERCASE   1
#define CONVERT_UNSIGNED    2

#define USE_GETLINE 0
#define USE_STRTOK  0

#define HIST_FILE   ".simple_shell_history"
#define HIST_MAX    4096

extern char **environ;

typedef struct liststr {
    int num;
    char *str;
    struct liststr *next;
} list_t;

typedef struct passinfo {
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

    char **cmd_buf;
    int cmd_buf_type;
    int readfd;
    int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
    0, 0, 0}

typedef struct builtin {
    char *type;
    int (*func)(info_t *);
} builtin_table;

int custom_shell_loop(info_t *, char **);
int find_builtin_command(info_t *);
void find_custom_command(info_t *);
void fork_custom_command(info_t *);

int is_command(info_t *, char *);
char *duplicate_characters(char *, int, int);
char *find_command_path(info_t *, char *, char *);

int loophsh(char **);

void _epstr(char *);
int _ech(char);
int _pfd(char c, int fd);
int _pstrfd(char *str, int fd);

int _len(char *);
int _compare(char *, char *);
char *_starts(const char *, const char *);
char *_concat(char *, char *);

char *_strcp(char *, char *);
char *_strdu(const char *);
void _putz(char *);
int _putch(char);

char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

char **strtow(char *, char *);
char **strtow2(char *, char);

char *_mymset(char *, char, unsigned int);
void myffree(char **);
void *my_realloc(void *, unsigned int, unsigned int);

int rzero(void **);

int checkInteractive(info_t *);
int isDelimiter(char, char *);
int isAlphabetic(int);
int stringToInteger(char *);

int _newtoi(char *);
void display_error(info_t *, char *);
int print_decimal(int, int);
char *num_converter(long int, int, int);
void erase_comments(char *);

int _xexit(info_t *);
int _cd(info_t *);
int _xhelp(info_t *);

int _myhistory(info_t *);
int _myalias(info_t *);

ssize_t gt_in(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

void reset_data(info_t *);
void initialize_data(info_t *, char **);
void release_data(info_t *, int);

char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

char **a(info_t *);
int c(info_t *, char *);
int h(info_t *, char *, char *);

char *_history_file(info_t *info);
int _write_history(info_t *info);
int _read_history(info_t *info);
int _build_history_list(info_t *info, char *buf, int linecount);
int _renumber_history(info_t *info);

list_t *add_list_node(list_t **, const char *, int);
list_t *add_list_node_end(list_t **, const char *, int);
size_t print_data_list(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_data_list(list_t **);

size_t ll_size(const list_t *);
char **ll_to_strs(list_t *);
size_t print_ll(const list_t *);
list_t *nd_sw(list_t *, char *, char);
ssize_t get_nd_idx(list_t *, list_t *);

int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif /* SHELL_H */

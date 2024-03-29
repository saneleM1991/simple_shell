#ifndef _SHELL_H_
#define _SHELL_H_

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
 *@arg: a string generated from getline
 *@argv: array of strings
 *@path: a string path
 *@argc: argument count
 *@line_count: error
 *@err_num: error code
 *@linecount_flag: if count this line
 *@fname: program name
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ
 *@history: the history node
 *@alias: the alias node
 *@env_changed: environ
 *@status: return status
 *@cmd_buf: address of pointer to cmd_buf
 *@cmd_buf_type: CMD_type
 *@readfd: the fd
 *@histcount: the history
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

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} infor_t;

#define INFO_INIT                                                               \
	{                                                                           \
		NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
			0, 0, 0                                                             \
	}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(infor_t *);
} builtin_table;

/* toem_shloop.c */
int hsh(infor_t *, char **);
int find_builtin(infor_t *);
void find_cmd(infor_t *);
void fork_cmd(infor_t *);

/* toem_parser.c */
int is_cmd(infor_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(infor_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* toem_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* toem_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* toem_exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* toem_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* toem_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int bfree(void **);

/* toem_atoi.c */
int isinteractive(infor_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* toem_errors1.c */
int _erratoi(char *);
void print_error(infor_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* toem_builtin.c */
int _ext(infor_t *);
int _cd(infor_t *);
int _help(infor_t *);

/* toem_builtin1.c */
int _myhistory(infor_t *);

/*toem_getline.c */
ssize_t get_input(infor_t *);
int _getline(infor_t *, char **, size_t *);
void sigintHandler(int);

/* toem_getinfo.c */
void clear_info(infor_t *);
void set_info(infor_t *, char **);
void free_info(infor_t *, int);

/* toem_environ.c */
char *_getenv(infor_t *, const char *);
int _myenv(infor_t *);
int _mysetenv(infor_t *);
int _myunsetenv(infor_t *);
int populate_env_list(infor_t *);

/* toem_getenv.c */
char **get_environ(infor_t *);
int _unsetenv(infor_t *, char *);
int _setenv(infor_t *, char *, char *);

/* toem_history.c */
char *get_history_file(infor_t *info);
int write_history(infor_t *info);
int read_history(infor_t *info);
int build_history_list(infor_t *info, char *buf, int linecount);
int renumber_history(infor_t *info);

/* toem_lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* toem_lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* toem_vars.c */
int is_chain(infor_t *, char *, size_t *);
void check_chain(infor_t *, char *, size_t *, size_t, size_t);
int replace_alias(infor_t *);
int replace_vars(infor_t *);
int replace_string(char **, char *);

#endif

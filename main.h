#ifndef MAIN_H

#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>

#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define BUF_SIZE 1024
#define TO_LOWER 1
#define TO_UNSIGNED 2

#define NORM_CMD 0
#define CHAIN_CMD 1
#define AND_CMD 2
#define OR_CMD 3

#define HIST_FILE ".simple_shell_history"
#define HIST_SIZE 4096

#define INFO_INIT \
{ NULL, 0, NULL, 0, 0, 0, 0, NULL, NULL, 0, NULL, NULL, \
	0, 0, NULL, NULL, NULL, 0 }

extern char **environ;

/**
 * struct list_str - Structure to represent a linked list of strings.
 * @num: Number associated with the element.
 * @str: Pointer to the string.
 * @next: Pointer to the next element in the linked list.
 */
typedef struct list_str
{
	int num;
	char *str;
	struct list_str *next;
} list_t;

/**
 * struct token_info - Structure to hold various information
 *		related to command execution.
 * @arg: String of arguments.
 * @argc: Number of arguments.
 * @argv: Array of arguments.
 * @linecount_flag: If the input line is counted.
 * @line_count: Number of line command to check.
 * @status: Status of the execution.
 * @err_num: Error number.
 * @file_name: The executable file name.
 * @path: Path to the command.
 * @readfd: File descriptor for reading.
 * @env: List of environment variables.
 * @env_strings: Array of environment strings.
 * @env_changed: Environment changed flag.
 * @history: History of commands.
 * @history_count: History count.
 * @alias: Aliases for commands.
 * @cmd_buf: Pointer to command chain buffer for memory management.
 * @cmd_buf_type: Type of command (CMD_type ||, &&, ;).
 */
typedef struct token_info
{
	char *arg;
	int argc;
	char **argv;

	int linecount_flag;
	unsigned int line_count;

	int status;
	int err_num;

	char *file_name;
	char *path;
	int readfd;

	list_t *env;
	char **env_strings;
	int env_changed;

	int history_count;
	list_t *history;

	list_t *alias;

	char **cmd_buf;
	int cmd_buf_type;

} info_t;

/**
 * struct built_in - Structure to represent a built-in command.
 * @type: The name/type of the built-in command.
 * @func: Pointer to the function that implements the command.
 */
typedef struct built_in
{
	char *type;
	int (*func)(info_t *);
} built_in_t;

/* string handlers */
int print_char(int);
void print_string(const char *);
int str_length(const char *);

char *start_with(char *, const char *);
char *str_dup(const char *);
int str_cmp(const char *, const char *);
int str_rpl(char **, char *);

char *str_n_cpy(char *, const char *, size_t);
char *str_n_cat(char *, const char *, int);
char *str_chr(char *, const char);
char *dup_str(const char *, int, int);

char **str_to_word(const char *, char *);
int num_words(const char *, const char *);
int is_delimiter(const char, const char *);
char *str_cpy(char *, const char *);

/* utils functions */
int interactive(info_t *);
int _err_atoi(const char *);
void print_err(info_t *, const char *);
int print_int(int, int);

char *convert_number(long int, int, int);
void remove_comments(char *);

/* errors handlers */
int print_err_char(int);
void print_err_string(const char *);

/* custom built-in shell hanlders */
int user_exit(info_t *);
int user_cd(info_t *);
int user_help(info_t *);
int user_history(info_t *);

/* environment handlers */
char *get_env(info_t *, const char *);
int set_env(info_t *, char *, char *);
int user_env(info_t *);
char **get_environ(info_t *);

int user_setenv(info_t *);
int user_unsetenv(info_t *);
int populate_env_list(info_t *);
int unset_env(info_t *, char *);

/* linked list handlers */
list_t *add_node_end(list_t **, const char *, int);
size_t print_list(const list_t *);
size_t print_list_string(const list_t *);
char **list_to_strings(list_t *);

size_t list_length(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* memory handlers */
char *_memset(char *, char, unsigned int);
void ffree(char **);
int Null_free(void **);
void *_realloc(void *, unsigned int, unsigned int);

/* history handlers */
char *get_history_file(info_t *);
int read_history(info_t *);
int build_history_list(info_t *, char *, int);
int renumber_history(info_t *);
int write_history(info_t *);

/* file handlers */
int print_chr_fd(const char, int);
int print_str_fd(const char *, int);

/* shell loop handlers */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* token info handlers */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* getline handlers */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* cmd utils */
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int is_cmd(info_t *, char *);
char *find_path(info_t *, char *, char *);
int is_chain(info_t *, char *, size_t *);

int replace_alias(info_t *);
int replace_vars(info_t *);

/* alias handler */
int user_alias(info_t *);

#endif

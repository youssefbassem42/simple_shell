#ifndef SHELL_LIB_H
#define SHELL_LIB_H

/*------- Used Libraries -------*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <stdbool.h>
/*-------Convert Numbers-------*/
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/*-------History-------*/
#define HISTORY_FILE "./.simple_shell_history"
#define HISTORY_MAX 4096

/*-------Command Chain-------*/
#define CMD_NORMAL 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/*-------Using Getline()-------*/
#define USE_STRTOK 0

/*-------Read && Write Buffers-------*/
#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

/*-------Delims for handling tokenizer-------*/
#define DEFAULT_DELIM " "

extern char **environ;

/**
 * struct list_string - linked list structure
 * @string: the string
 * @number: number field
 * @next: point to next node
 */
typedef struct list_string
{
	char *string;
	int number;
	struct list_string *next;
} list_t;

/**
 * struct passing_info - all arguments required to pass into functions
 * @status: return the last command executed
 * @cmd_buffer: storing the address of the pointer if it chaining
 * @cmd_buff_type: || , && , ;
 * @readfd: read line input
 * @histcount: history line counter
 * @argument: entred argument by the user handled with getline function
 * @argv: array of strings to passed arguments
 * @path: the path of the current command line inputed
 * @argc: number of argument passed
 * @env: local copy of the environment in linkedlist
 * @history: histroy node
 * @alias: alias node
 * @environ: environment variable
 * @env_changed: checked if the environment has changed
 * @line_counter: error counter
 * @erro_number: error code for exit statue
 * @linecount_flag: count of  lines inputed
 * @filename: the file name
*/
typedef struct passing_info
{
	int status;
	char *argument;
	char **argv;
	char *path;
	int argc;
	unsigned int line_counter;
	int erro_number;
	int linecount_flag;
	char *filename;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	char **cmd_buffer;
	int cmd_buff_type;
	int readfd;
	int histcount;
	list_t *env;
} info;

/*Initializing values for Info Struct*/
#define INFO_INIT \
{0, NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, 0, NULL, 0,\
		 0, 0, NULL}

/**
 * struct built_in - contain builtin string and related function
 * @function: Function
 * @type: the Command Flag
 */
typedef struct built_in
{
	char *type;
	int (*function)(info *);
} built_in;


/*------- String Manipulation -------*/
int _putchar(char ch);
void _puts(char *string);
int _strlen(char *string);
char *_strcpy(char *first_1, char *source_1);
char *start_with(const char *, const char *);
char *str_concationation(char *s1, char *s2);
int _strcmp(char *string_1, char *string_2);
char *_strdup(const char *string);

/*------- Tokenizer File -------*/
int is_delim(char c, const char *delim);
char **strtoken(const char *str, const char *delims);

/*------- Memory Management -------*/
int frees(void **pointer);
char *_memory_inisializer(char *ptr, char value, unsigned int  size);
void *_realloc(void *pointer, unsigned int old_size, unsigned int new_size);
void free_str(char **string);

/*------- Linked List Functions -------*/
list_t *add_first(list_t **head, const char *string, int number);
size_t list_length(const list_t *list);
int delete_at(list_t **head, unsigned int index);
list_t *add_end(list_t **head, const char *string, int number);
void list_is_free(list_t **head);
size_t print_string(const list_t *head);
size_t list_printer(const list_t *head);
list_t *node_searcher(list_t *head, char *pre, char second);
ssize_t get_index(list_t *head_point, list_t *the_node);
char **strings_of_list(list_t *head);

/*------- Getline Build -------*/
void fix_sigint(int);
int _getline(info *info, size_t *size, char **pointer);
ssize_t input_getter(info *info);

/*------- Parser Control -------*/
char *path_finder(info *info, char *path_string, char *command);
int is_command(info *info, char *Path);
char *string_dupicator(char *path_str, int s, int sp);

/*------- Interactive Handler -------*/
int is_interactive(info *info);
/*------- Info Control -------*/
void clear_info(info *info, int v);
void delete_info(info *info);
void init_info(info *info, char **string);

/*------- Variables Handle -------*/
int string_changer(char **o, char *n);
int alias_changer(info *info);
int is_chain(info *info, char *buffer, size_t *ptr);
void chain_checker(info *info, char *buffer,
	 size_t *pos, size_t st, size_t length);
int var_change(info *info);

/*------- Shell Prompt -------*/
int prompt(info *info, char **argument);
void command_fork(info *info);
int builtin_finder(info *info);
void command_finder(info *info);

/*------- Commands -------*/
int cder(info *info);
int exit_ex(info *info);
int history_saver(info *info);
int _alias(info *info);
int alias_printer(list_t *ptr);
int alias_def(info *info, char *string);
int clear_alias(info *info, char *string);
/*------- Environment -------*/
int _env(info *info);
int env_init(info *info);
char *_getenv(info *info, const char *n);
int un_env(info *info);
int env_list(info *info);

/*------- Environment Handle Functions -------*/
int env_set(info *info, char *v, char *en_v);
int clear_env(info *info, char *v);
char **env_getter(info *info);

/*------- Error Handle Functions -------*/
int _putfiled(char s, int file);
int err_putchar(char s);
void err_put(char *e);
int putsfiled(char *string, int filed);
int decimal_printer(int i, int filed);
void error_poper(info *info, char *err);
int atoi_error(char *string);
void delete_comment(char *buffer);
char *number_converter(long int number, int base, int flag);

/*------- History -------*/
int history_build(info *info, char *buffer, int line);
int in_history(info *info);
char *get_history(info *info);
int reinit_history(info *info);
int out_history(info *info);

/*------- Exit -------*/
char *str_char(char *s, char c);
char *_strncat(char *dest, char *src, int n);
char *_strncpy(char *dest, char *src, int n);
#endif

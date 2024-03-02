#ifndef _SHELL_H_
#define _SHELL_H_


#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>




/* Reading and writing buffers */
#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1



/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* new chain */
#define NORMAL_COMMAND 0
#define OR_COMMAND		1
#define AND_COMMAND		2
#define CHAIN_COMMAND	3

#define HISTORY_FILE	".shell_history"
#define HISTORY_MAXIMUM	4096

extern char **environ;


/**
 * struct liststr - a singly linked list
 * @n: the number field
 * @str: the string field
 * @next: a pointer to the next node
*/
typedef struct liststr
{
    int n;
    char *str;
    struct liststr *next;
} list_a;

/**
 * struct CommandInfo - contains pseudo-arguments for passing into a function,
 *		enabling a consistent prototype for a function pointer struct
 * @argument_string: a string generated from getline containing function arguments
 * @argument_array: an array of strings generated from argument_string
 * @command_path_str: a string representing the path for the current command
 * @argument_count: the count of arguments
 * @line_number: the line number in the input
 * @error_number: the error code for exit() operations
 * @count_line_flag: a flag indicating whether to count this line of input
 * @file_name_str: the filename of the program
 * @environment_list: a linked list representing the local copy of the environment
 * @history_node: the history node for tracking previous commands
 * @alias_node: the alias node for managing command aliases
 * @custom_environment: a custom-modified copy of the environment stored in a linked list
 * @environment_changed_flag: a flag indicating whether the environment was changed
 * @execution_status: the return status of the last executed command
 * @command_buffer_pointer: a pointer to the command buffer, used for memory management
 * @command_buffer_type: CMD_type representing the type of command chaining (||, &&, ;)
 * @read_file_descriptor: the file descriptor from which to read line input
 * @history_line_count: the count of lines in the command history
 */
typedef struct CommandInfo
{
	char *argument_string;
	char **argument_array;
	char *command_path_str;
	int argument_count;
	unsigned int line_number;
	int error_number;
	int count_line_flag;
	char *file_name_str;
	list_a *environment_list;
	list_a *history_node;
	list_a *alias_node;
	char **custom_environment;
	int environment_changed_flag;
	int execution_status;

	char **command_buffer_pointer; /* pointer to command ; chain buffer, for memory management */
	int command_buffer_type; /* CMD_type ||, &&, ; */
	int read_file_descriptor;
	int history_line_count;
} myInfoType;


#define MY_CUSTOM_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}



/**
 *struct CustomBuiltin - contains a custom builtin command string and its associated function
 *@command_type: the flag representing the custom builtin command
 *@command_function: the function pointer to the associated custom builtin function
 */
typedef struct customBuiltin
{
	char *command_type;
	int (*command_function)(myInfoType *);
} customBuiltinTable;

/* alloc.c */
char *_memset(char *s, char b, unsigned int n);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* prototype for env.c */
char **get_environment(myInfoType *);
int custom_unset_environment_variable(myInfoType *, char *);
int custom_set_environment_variable(myInfoType *, char *, char *);


/* prototype for error2.c */
void custom_print_error_string(char *);
int custom_write_to_stderr(char ch);
int custom_write_to_fd(char, int);
int custom_puts_to_fd(char *, int fd);


/* prototype for errors.c */
int custom_atoi(char *);
void display_custom_error(myInfoType *, char *);
int print_custom_number(int, int);
char *custom_itoa(long int, int, int);
void custom_trim_comments(char *);

/* exit.c */
char *_strncpy(char *dest, char *src, int n);
char *_strncat(char *dest, char *src, int n);
char *_strchr(char *s, char c);


/* freeme.c */
void resetting(myInfoType *);
void finallyfree(char **);
int pfree(void **);

/* getcommands */
void initiate_custom_info(myInfoType *, char **);

/* getenv.c */
int envMine(myInfoType *);
char *customGetenv(myInfoType *, const char *);
int newSetenv(myInfoType *);
int newUnsetenv(myInfoType *);
int listOfenviroment(myInfoType *);

/* prototyoe for getline */
ssize_t get_line(myInfoType *custominfo, char **commands, size_t *length);
ssize_t get_commands(myInfoType *custominfo);
ssize_t readCommands(myInfoType *, char *, size_t *);
int _getline(myInfoType *c, char **, size_t *);
void handle_signal(__attribute__((unused))int signum);

/* hist.c */
char *hist_file(myInfoType *);
int hist_pen_write(myInfoType *);
int hist_read(myInfoType *custominfo);
int bhistlist(myInfoType *custominfo, char *, int linecount);
int history_renumbering(myInfoType *);

/* implement2.c */
int histmine(myInfoType *);
int aliasSetnot(myInfoType *, char *);
int aliasSet(myInfoType *, char *);
int display_alias(list_a *);
int mimic_alias(myInfoType *);

/* implementBuiltin.c */
int exitingIsmine(myInfoType *);
int chWorDir(myInfoType *);
int helpMe(myInfoType *);

/* interactive */
int interactive(myInfoType *);
int delim(char c, char *char_delim);

/* prototype for listfunc.c */
size_t list_len(const list_a *);
char **linked_list_to_array(list_a *);
size_t print_custom_list(const list_a *);
list_a *find_matching_node(list_a *, char *, char);
ssize_t get_index_of_node(list_a *, list_a *);


/* prototype for listfunc2.c */
list_a *add_node_at_start(list_a **, const char *, int);
list_a *add_node_end(list_a **, const char *, int);
int delete_node_at_index(list_a **, unsigned int);
void free_list(list_a **);

/* main.c */


/* prompt.c */
int character_flush(char c);
void free_command(myInfoType *, int all);


/* shellme.c  */
int shell(myInfoType *, char **);
int lookSysCommand(myInfoType *);
void find_command(myInfoType *);
void exec_cmd(myInfoType *);


/* split.c */
char **spiltString(char *string, char *char_delim);
char **spiltString2(char *string, char char_delim);


/* prototype for string_utils.c */
int _stringLength(char *str);
int _stringCompare(char *str1, char *str2);
char *_startsWith(const char *haystack, const char *needle);
char *_stringConcatenate(char *destination, char *source);


/* prototype for string_utils1.c */
char *_strcpy_custom(char *dest, char *src);
char *_strdup_custom(const char *str);
void _puts_custom(char *str);
int _putchar_custom(char c);

/* prototype for utilscommand */
int is_executable(myInfoType *, char *);
char *multiple(char *, int , int );
char *find_path(myInfoType *, char *, char *);
char *pathing(myInfoType *custominfo, char *pathwaystr, char *command);

/* variables */
int chaining(myInfoType *, char *, size_t *);
void chainKeche(myInfoType *, char *, size_t *, size_t, size_t );
int r_alias(myInfoType *);
int r_vars(myInfoType *custominfo);
int r_string(char **old, char *new);

#endif /* End of header file */

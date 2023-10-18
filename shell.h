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

extern char **environ;

/**
 * struct strlist - singly linked list
 * @node_num: the number field
 * @str: a string
 * @next: points to the next node
 */

typedef struct strlist
{
	int node_num;
	char *str;
	struct strlist *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @count_line: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @program_name: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfileDes: the filedes from which to read line input
 * @histcount: the history line number count
 */

typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int count_line;
	int err_num;
	int linecount_flag;
	char *program_name;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buff;   /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buff_type; /* CMD_type ||, &&, ; */
	int readfileDes;
	int histcount;
} info_t;

#define INFO_INIT                                                               \
	{                                                                           \
	NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0                                                             \
	}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

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

/* for read/write buffers */
#define READ_BUFF_SIZE 1024
#define WRITE_BUFF_SIZE 1024
#define BUFF_FLUSH -1

/* checkfun.c */
int check_alpha(int C);
int check_delim(char C, char *del);
int interact_mood(info_t *info);
int str_int(char *str)

    // stringFUN1.c
int str_len(char *s);
char *str_con(char *dest, char *src);
int str_cmp(char *s1, char *s2);
char *str_cpy(char *dest, char *src);
char *startWith(const char *haystack, const char *needle);

// stringFUN2.c
int _putchar(char c);
void _puts(char *str);
char *str_dup(const char *str);

// stringFUN3.c
char *_strNcpy(char *dest, char *src, int Nchar);
char *_strchr(char *s, char C);
char *_strNcon(char *dest, char *src, int N);

// stringFUN4.c
char **splitstr1(char *str, char del);
char **splitstr2(char *str, char *del);

// memory_FUN.c
void *New_alloc(void *Old_ptr, unsigned int Old_Memory, unsigned int New_Memory);
int ptr_free(void **address);
char *fills_memory(char *ptr, char byte, unsigned int byteNum);
void free_string(char **ptr_str);

// shell_errors1.c
int error_putchar(char C);
void error_puts(char *str);
int write_fileDes(char C, int fileDes);
int puts_fileDes(char *str, int fileDes);
void comment_eliminate(char *buff);

// shell_errors2.c
int errstr_int(char *str);
void error_output(info_t *info, char *errstr);
int print_decimal(int input, int fileDes);
char *int_str(long int num, int base, int flags);

// linked_list1
list_t *my_node(list_t **old_head, const char *str, int node);
list_t *node_endADD(list_t **head, const char *str, int num);
size_t mylist_StrPrint(const list_t *firstNode);
int NodeRemove(list_t **head, unsigned int Nodeindex);
void mylistFREE(list_t **head_address);

// linkes_list2
size_t mylistLength(const list_t *firstNode);
char **listStr(list_t *head);
size_t mylistPrint(const list_t *firstNode);
list_t *mynode_starts(list_t *node, char *strtext, char C);
ssize_t mynode_index(list_t *head, list_t *node);

// getENV
char **get_environment(info_t *info);
int unset_enviorn(info_t *info, char *varenv);
int set_MYenviron(info_t *info, char *varenv, char *value);

// env
int MYenvironment_Print(info_t *info);
char *get_MYenviornment(info_t *info, const char *VARname);
int set_myNEW_environ(info_t *info);
int unset_MYenv(info_t *info);
int enviorn_listPOP(info_t *info);

// shell_IO_fun.c
char *getSHELL_historyFile(info_t *info);
int write_SHELLhistory(info_t *info);
int read_SHELLhistory(info_t *info);
int build_MYhistoryList(info_t *info, char *buff, int lineCount);
int recount_MYhistory(info_t *info);

// vars_chain.c
int check_BUFFchain(info_t *info, char *buff, size_t *ptr);
void check_ischain(info_t *info, char *buff, size_t *ptr, size_t i, size_t buff_len);
int alias_Replace(info_t *info);
int var_Replace(info_t *info);
int string_Repalce(char **oldStr, char *newStr);

// path_find.c
int check_cmd(info_t *info, char *path);
char *chars_Dupl(char *pathstr, int start, int stop);
char *MYpath(info_t *info, char *pathstr, char *cmd);

// shell_INFO.c
void clearMYinfo(info_t *info);
void setMYinfo(info_t *info, char **av);
void freeMYinfo(info_t *info, int all);

// builtin_fun1.c
int myshell_exit(info_t *info);
int mychange_dir(info_t *info);
int myshell_help(info_t *info);

// builtin_fun2.c
int display_myhistory(info_t *info);
int alias_UNset(info_t *info, char *str);
int alias_SET(info_t *info, char *str);
int alias_Print(list_t *node);
int man_Alias(info_t *info);

// line_get.c
ssize_t buff_INput(info_t *info, char **buff, size_t *var_len);
ssize_t input_get(info_t *info);
ssize_t buff_READ(info_t *info, char *buff, size_t *i);
int line_gets(info_t *info, char **ptr, size_t *length);
void sigintHandler(__attribute__((unused))int sig_num);

// shell_LOOP.c
int shell_loop(info_t *info, char **av);
int builtin_FIND(info_t *info);
void cmd_FIND(info_t *info);
void CMD_fork(info_t *info);

#endif

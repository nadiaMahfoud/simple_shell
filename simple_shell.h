#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <signal.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stddef.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>

/* FOR MSG HELP AND PROMPT */
#include "util.h"

/* PROGRAM STRUCTURES */

/**
 * struct ProgramData - this is the structure to hold the program_related data
 * @name: name of the prgram's executable
 * @in: the pointer to the input read from line_reader
 * @cmd: the pointer to the first cmd entered by the USER
 * @ctr_exe: count of the executed cmds
 * @fd: the file descriptor for cmd input
 * @t: the pointer to tokens representing the parsed inputt
 * @env_cpy: copy of the program's environment variables
 * @aliases: Alias pointers array
 */

typedef struct ProgramData
{
	char *name;
	char *in;
	char *cmd;
	int ctr_exe;
	int fd;
	char **t;
	char **env_cpy;
	char **aliases;
} prog_data;

/**
 * struct builtins - THe structure definition for BUILTin cmds
 * @builtin: The name of the builtin_cmd
 * @function: ThE associated function to be called for each builtin_cmd
 */

typedef struct builtins
{
	char *builtin; /* Name of the builtin cmd*/
	int (*function)(prog_data *prog); /*Ptr to builtin cmd function */
} builtin_info;

/***********************FUNCTIONS PROTOTYPES********************/

/* SHOW HELP FUNCTION */

int show_help(prog_data *prog);

/* INPUT READER FUNCTION */

int line_reader(prog_data *prog);

/* Aliases functions */

int display_aliases(prog_data *prog, char *alias_name);
char *retrieve_alias(prog_data *prog, char *name);
int define_alias(char *alias_string, prog_data *prog);
int manage_alias(prog_data *prog);
void process_aliases(prog_data *prog);

/* Environment functions */

int exe_env_command(prog_data *prog);
int init_environment(prog_data *prog);
int unset_environment(prog_data *prog);
char *update_environment_val(char *cle, prog_data *prog);
int set_environment(char *cle, char *val, prog_data *prog);
int delete_environment_key(char *cle, prog_data *prog);
void show_environment(prog_data *prog);

/* FREE MEMORY FUNCTIONS */

void free_recur(prog_data *prog);
void free_ptrs(char **ptrs);
void free_data(prog_data *prog);

/*NUMBERS HANDLING FUNCTIONS */

int str_to_int(char *s);
int char_occ(char *str, char *a);
void l_to_str(long numb, char *str, int b);

/* STRING HANDLING FUNCTIONS */

void tok(prog_data *prog);
int str_comp(char *str1, char *str2, int cmp);
int str_len(char *str);
char *str_cat(char *dest, char *src);
void str_rev(char *s);
char *str_dup(char *str);
char *str_split(char *src, char *sep);

/* PRINT TEXT TO STDOUT AND STDERR FUNCTIONS */

int p_stdout(char *s);
int p_stderr(char *s);
int p_merr(int code, prog_data *prog);

/* MAIN PROGRAM FUNCTIONS */

void ctrl_c_handler(int opr UNUSED);
void init_data(prog_data *prog, int targc, char *argv[], char **env_cpy);
void runShell(char *prompt, prog_data *prog);
int main(int agrc, char *argv[], char *env_cpy[]);

/* COMMAND FUNCTIONS */

int execute_cmd(prog_data *prog);
int show_builtin_cmd(prog_data *prog);
int find_exec(prog_data *prog);
int process_logic_operators(char *command_array[], int index,
		char operator_array[]);

/* PATH FUNCTIONS */

int path_valid(char *path);
char **tok_environment_path(prog_data *prog);
int change_dir(prog_data *prog);
int set_working_dir(prog_data *prog, char *new_direct);

/* OTHER FUNCTIONS */

void process_var(prog_data *prog);
int buffer_append(char *buf, char *s_to_add);
int exit_shell(prog_data *prog);

#endif

#ifndef HELP_H
#define HELP_H

/* Message to be siplayed as the command prompt*/
#define PROMPT_MSG "Enter your cmd:"

/* Size of buffer used for each read operation in line_reader*/
#define BUFFER_SIZE 1024

/*Unused attribute for compileroptimization*/
#define UNUSED __attribute__((unused))

/* The predefined help msgs for builtin commands*/

#define EXIT_HELP "exit: ExIt the simple_shell!\n" \
		  "	Usage: exit [status]\n" \
		  "	ExIting the simple_shell, it sets the status to N\n" \
		  "	if N not provided, exit status = most recently\n" \
		  "	executed cmd\n"
#define CD_HELP "cd: Changethe directory currently in use!\n" \
		"	Usage: cd [dir]\n" \
		"	If no argument is provided, the command will change\n" \
		"	to the home dir!.\n" \
		"	If the argument is a hyphen (-), the command will\n" \
		"	change to the previous dir!.\n"
#define ENV_HELP "env_cpy: Display the environment_variables!\n" \
		"	Usage: env_cpy\n" \
		"	The env_cpy command shows a full list\n" \
		"	of the env var.\n"
#define SETENV_HELP "setenv: Modify of add an environment_variables!\n" \
		    "	Usage: setenv VARIABLE VALUE\n" \
		    "	Create or Update the env var\n" \
		    "	Prints error msg when an incorrect num of args\n" \
		    "	is provided\n"
#define UNSETENV_HELP "unsetenv: Remove an environment_variable!\n" \
			"	Usage: unsetenv VARIABLE\n" \
			"	This function removes a variable from the\n" \
			"	system environment\n" \
			"	Prints error msg when incorrect num of args\n" \
			"	is provided\n"
#define HELP_MSG "help: Provides details on builtin commands!\n" \
		"	Usage: help [CMD_BUILTIN]\n" \
		"	Provides concise summaries of builyin commands\n" \
		"	IF CMD_BUILTIN is providedd, it presents in_depth\n" \
		"	assistance on commands that match the specified\n" \
		"	name. Otherwise, it lists the available helptopics\n" \
		"	Available CMD_BUILTIN!:\n" \
		"	exit [status]\n" \
		"	cd [dir]\n" \
		"	env_cpy\n" \
		"	setenv [variable value]\n" \
		"	unsetenv [variable]\n" \
		"	help [cmd_builtin]\n"

#endif

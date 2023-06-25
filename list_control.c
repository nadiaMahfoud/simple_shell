#include "simple_shell.h"


/**
 * execute_builtin_function - searches for a match
 * and executes the associated builtin
 * @prog: struct for the program's data
 * Return: Returns the return value of the executed
 * function if there is a match,
 * otherwise returns -1.
 **/
int execute_builtin_function(prog_data *prog)
{
	int it;

	builtin_info opt[] = {
		{"exit", exit_shell},
		{"help", show_help},
		{"cd", change_dir},
		{"alias_name", manage_alias},
		{"env", exe_env_command},
		{"setenv", set_environment},
		{"unsetenv", unset_environment},
		{NULL, NULL}
	};
	/* Walk through the structure */
	for (it = 0; opt[it].builtin != NULL; it++)
	{/* If there is a match between the given command and a builtin */
		if (str_comp(opt[it].builtin, prog->cmd, 0))
		{/* Execute the function and return its return value */
			return (opt[it].function(prog));
		}
	}
	/* If there is no match, return -1 */
	return (-1);
}

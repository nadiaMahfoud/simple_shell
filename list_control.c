#include "simple_shell.h"


/**
 * show_builtin_cmd - to look for a match
 * and execute the associated builtin
 * @prog: structure for the program's data
 * Return: Returns the return value of the executed
 * function if there's a match,
 * otherwise it returns -1.
 **/
int show_builtin_cmd(prog_data *prog)
{
	int it;

	builtin_info opt[] = {
		{"exit", exit_shell},
		{"help", show_help},
		{"cd", change_dir},
		{"alias_name", manage_alias},
		{"env", exe_env_command},
		{"setenv", init_environment},
		{"unsetenv", unset_environment},
		{NULL, NULL}
	};
	/* Walk along the structure */
	for (it = 0; opt[it].builtin != NULL; it++)
	{/* If there's a match between the given command and a builtin */
		if (str_comp(opt[it].builtin, prog->cmd, 0))
		{/* To Execute the function and return its return value */
			return (opt[it].function(prog));
		}
	}
	/* If there's no match, return -1 */
	return (-1);
}

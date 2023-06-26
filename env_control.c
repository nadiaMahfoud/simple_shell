#include "simple_shell.h"

/**
 * exe_env_command - To Display the environment in which the shell runs
 * @prog: structure for the program's data
 * Return: 0 if success, or other number if it's declared in the arguments
 */

int exe_env_command(prog_data *prog)
{
	int n;
	char var_name[50] = {'\0'};
	char *value_copy = NULL;

	/* if it's not arguments */
	if (prog->t[1] == NULL)
		show_environment(prog);
	else
	{
		for (n = 0; prog->t[1][n]; n++)
		{/* checks if exists a char = */
			if (prog->t[1][n] == '=')
			{ /* checks if exists a var with the same name */
				/* and change its value temporally */
				value_copy = str_dup(update_environment_val(var_name, prog));
				if (value_copy != NULL)
					set_environment(var_name, prog->t[1] + n + 1, prog);
				/* to print the environment */
				show_environment(prog);
				if (update_environment_val(var_name, prog) == NULL)
				{ /* prints the var if it doesn't exist in the environment */
					p_stdout(prog->t[1]);
					p_stdout("\n");
				}
				else
				{ /* returns the previous value of the var*/
					set_environment(var_name, value_copy, prog);
					free(value_copy);
				}
				return (0);
			}
			var_name[n] = prog->t[1][n];
		}
		errno = 2;
		perror(prog->cmd);
		errno = 127;
	}
	return (0);
}

/**
 * init_environment - It Displays the environment in which the shell is running
 * @prog: structure for the program's data
 * Return: 0 if success, or other number if it's declared in the arguments
 */
int init_environment(prog_data *prog)
{
	/* To validate the  args */
	if (prog->t[1] == NULL || prog->t[2] == NULL)
		return (0);
	if (prog->t[3] != NULL)
	{
		errno = E2BIG;
	perror(prog->cmd);
		return (5);
	}
	set_environment(prog->t[1], prog->t[2], prog);

	return (0);
}

/**
 * unset_environment - Displays the environment in which the shell is running
 * @prog: structure for the program's data
 * Return: 0 if success, or other number if it's declared in the args
 */
int unset_environment(prog_data *prog)
{
	/* validate args */
	if (prog->t[1] == NULL)
	{
		errno = E2BIG;
		perror(prog->cmd);
		return (5);
	}
	delete_environment_key(prog->t[1], prog);

	return (0);
}



#include "simple_shell.h"

/**
 * exit_shell - To Exit the program with the status.
 * @prog: structure for the program's data.
 *
 * Return: 0 if success, or other number if it's declared in the arguments.
 */
int exit_shell(prog_data *prog)
{
	int x;

	if (prog->t[1] != NULL)
	{
		/* If an argument exists for exit, check if it's a number */
		for (x = 0; prog->t[1][x]; x++)
		{
			if ((prog->t[1][x] < '0' || prog->t[1][x] > '9') &&
					prog->t[1][x] != '+')
			{
				errno = 2;
				return (2);
			}
		}
		errno = _atoi(prog->t[1]);
	}
	free_data(prog);
	exit(errno);
}

/**
 * change_dir - To Change the current directory.
 * @prog: structure for the program's data.
 *
 * Return: 0 if success, or other number if it's declared in the arguments.
 */

int change_dir(prog_data *prog)
{
	char *home_dir = find_environment_var("HOME", prog);
	char *direct_old = NULL;
	char old_direct[128] = {0};
	int code_error = 0;

	if (prog->t[1])
	{
		if (str_comp(prog->t[1], "-", 0))
		{
			direct_old = find_environment_var("OLDPWD", prog);

			if (direct_old)
				code_error = set_working_dir(prog, direct_old);
			p_stdout(find_environment_var("PWD", prog));
			p_stdout("\n");

			return (code_error);
		}
		else
		{
			return (set_working_dir(prog, prog->t[1]));
		}
	}
	else
	{
		if (!home_dir)
			home_dir = getcwd(old_direct, 128);
		return (set_working_dir(prog, home_dir));
	}
	return (0);
}

/**
 * set_working_dir - To Set the working directory.
 * @prog: structure for the program's data.
 * @new_direct: Path to be set as the working directory.
 *
 * Return: 0 if success, or other number if it's declared in the arguments.
 */

int set_working_dir(prog_data *prog, char *new_direct)
{
	char old_direct[128] = {0};
	int error_code = 0;

	getcwd(old_direct, 128);

	if (!str_comp(old_direct, new_direct, 0))
	{
		error_code = chdir(new_direct);
		if (error_code == -1)
		{
			errno = 2;
			return (3);
		}
		update_environment_val("PWD", new_direct, prog);
	}
	update_environment_val("OLDPWD", old_direct, prog);
	return (0);
}

/**
 * show_help - To Show the environment where the shell runs.
 * @prog: structure for the program's data.
 *
 * Return: 0 if success, or other number if it's declared in the arguments.
 */
int show_help(prog_data *prog)
{
	int x, len = 0;
	char *msg[6] = {NULL};

	msg[0] = HELP_MSG;

	/* Validate arguments */
	if (prog->t[1] == NULL)
	{
		p_stdout(msg[0] + 6);
		return (1);
	}
	if (prog->t[2] != NULL)
	{
		errno = E2BIG;
		perror(prog->cmd);
		return (5);
	}
	msg[1] = EXIT_HELP;
	msg[2] = ENV_HELP;
	msg[3] = SETENV_HELP;
	msg[4] = UNSETENV_HELP;
	msg[5] = CD_HELP;

	for (x = 0; msg[x]; x++)
	{
		/* Print the length of the string */
		len = str_len(prog->t[1]);

		if (str_comp(prog->t[1], msg[x], len))
		{
			p_stdout(msg[x] + len + 1);
			return (1);
		}
	}
	/* If there is no match, print error and return -1 */
	errno = EINVAL;
	perror(prog->cmd);
	return (0);
}



/**
 * manage_alias - To Add, remove, or show aliases.
 * @prog: structure for the program's data.
 *
 * Return: 0 if success, or other number if it's declared in the arguments.
 */
int manage_alias(prog_data *prog)
{
	int x = 0;

	/* If there are no arguments, print all aliases */
	if (prog->t[1] == NULL)
		return (display_aliases(prog, NULL));

	while (prog->t[++x])
	{
		/* If there are arguments, set or print each alias */
		if (char_occ(prog->t[x], "="))
			update_environment_val(prog->t[x], prog);
		else
			display_aliases(prog, prog->t[x]);
	}
	return (0);
}

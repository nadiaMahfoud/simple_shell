#include "simple_shell.h"

/**
 * free_recur - this function frees the memory used by various fields
 * within the prog_data structure each iteration
 * @prog: Prog_data Structure
 * Return: Void
 */

void free_recur(prog_data *prog)
{
	if (prog->t) /* t is the variable used for token */
		free_ptrs(prog->t);
	if (prog->in) /*in is the variable used for the input line*/
		free(prog->in);
	if (prog->cmd) /* cmd is the var used for the command chosenbyuser*/
		free(prog->cmd);
	prog->t = NULL;
	prog->in = NULL;
	prog->cmd = NULL;
}

/**
 * free_ptrs - This function is responsible for freeing each individual
 * pointer within array ofpointers and then freeing the array itself.
 * @ptrs: Array of pointers
 * Return: void
 */

void free_ptrs(char **ptrs)
{
	int idx = 0;

	if (ptrs != NULL)
	{
		for (; ptrs[idx]; idx++)
			free(ptrs[idx]);
		free(ptrs);
		ptrs = NULL;
	}
}

/**
 * free_data - ThIs function frees all fields of the prog_data structure
 * @prog: Prog_data structure
 * Return: void
 */

void free_data(prog_data *prog)
{
	if (prog->fd != 0)
	{
		if (close(prog->fd))
			perror(prog->name);
	}
	free_recur(prog);
	free_ptrs(prog->env_cpy);
	free_ptrs(prog->aliases);
}

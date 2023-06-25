#include "simple_shell.h"

/**
 * execute_cmd - Execute a command with its entire path variables.
 * @prog: A pointer to the program's data.
 *
 * Return: If success returns 0, otherwise, return -1.
 */
int execute_cmd(prog_data *prog)
{
	pid_t pid;
	int reval = 0, stat;

	/* To Check for program in built-ins */
	reval = show_builtin_cmd(prog);
	if (reval != -1) /* If program is found in built-ins */
		return (reval);

	/* To Check for program in file system */
	reval = find_exec(prog);
	if (reval) /* If program isn't found */
	{
		return (reval);
	}
	else /* If program found */
	{
		pid = fork(); /* Create a child process */
		if (pid == -1) /* If the fork call failed */
		{
			perror(prog->cmd);
			exit(EXIT_FAILURE);
		}
		if (pid == 0) /* I am the child process, I execute the program */
		{
			reval = execve(prog->t[0], prog->t, prog->env_cpy);
			if (reval == -1) /* If error when execve */
			{
				perror(prog->cmd);
				exit(EXIT_FAILURE);
			}
		}
		else /* I am the parent, I wait and check the exit status of the child */
		{
			wait(&stat);
			if (WIFEXITED(stat))
				reval = WEXITSTATUS(stat);
			else if (WIFSIGNALED(stat))
				reval = 128 + WTERMSIG(stat);
		}
	} return (0);
}

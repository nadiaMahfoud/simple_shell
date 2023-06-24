#include "simple_shell.h"

/**
 * ctrl_c_handler - In this function when the program receives
 * the SIGINT signal (Ctrl+C), outputs the prompt on a new line
 * @UNUSED: This parameter is not used within the function
 * Return: void
 */

void ctrl_c_handler(int opr UNUSED)
{
	p_stdout("\n");
	p_stdout(PROMPT_MSG);
}

/**
 * init_data - ThiS function sets up the program's data structure
 * @prog: the pointer to data structure
 * @argc: the number of commands arguments
 * @argv: array of command arguments
 * @env_cpy: env variables provided to the program
 * Return: void
 */

void init_data(prog_data *prog, int argc, char *argv[], char **env_cpy)
{
	int idx = 0;

	prog->name = argv[0];
	prog->in = NULL; /*initialize input*/
	prog->cmd = NULL; /*initialize command*/
	prog->ctr_exe = 0; /*setting the executionncounter to 0*/
	/*setting the file dexcriptor for reading*/
	if (argc == 1)
		prog->fd = STDIN_FILENO;
	else
	{
		prog->fd = open(argv[1], O_RDONLY);
		if (prog->fd == -1)
		{
			p_stderr(prog->name);
			p_stderr(": 0: Can't open ");
			p_stderr(argv[1]);
			p_stderr("\n");
			exit(127);
		}
	}
	prog->t = NULL;
	prog->env_cpy = malloc(sizeof(char *) * 50);
	if (env_cpy)
	{
		for (; env_cpy[idx]; idx++)
		{
			prog->env_cpy[idx] = str_dup(env_cpy[idx]);
		}
	}
	prog->env_cpy[idx] = NULL;
	env_cpy = prog->env_cpy;

	prog->aliases = malloc(sizeof(char *) * 20);
	for (idx = 0; idx < 20; idx++)
	{
		prog->aliases[idx] = NULL;
	}
}

/**
 * runShell - this function runs an infinite loop
 * that displays the shell prompt
 * @prompt: the text that will be displayed as the prompt
 * @prog: infinite loop for displaying the prompt
 * Return: void
 */

void runShell(char *prompt, prog_data *prog)
{
	int err = 0; /* setting the error code to zero*/
	int len = 0; /* the string length*/

	while (++(prog->ctr_exe))
	{
		p_stdout(prompt); /*print the shell_prompt*/
		err = len = line_reader(prog); /*read input &store len & err*/
		if (err == EOF)
		{
			free_data(prog);
			exit(errno); /* if EOF is the first char exit*/
		}
		if (len >= 1)
		{
			process_aliases(prog); /*process input aliases*/
			process_var(prog); /*process any var in input*/
			tok(prog); /*tokenize the input into commands*/
			if (prog->t[0])
			{
				/*start execution if any prompt*/
				err = execute_cmd(prog);
				if (err != 0)
					p_merr(err, prog);
			}
			free_recur(prog); /*free allocated mem*/
		}
	}
}
/**
 * main - this programsets up the program's data structure
 * @argc: the number of command line arguments
 * @argv: array of command line arguments
 * @env_cpy: environment variables provided to the program
 * Return: 0(success)
 */

int main(int argc, char *argv[], char *env_cpy[])
{
	char *prompt = "";
	prog_data prog_info = {NULL};
	prog_data *prog = &prog_info;

	init_data(prog, argc, argv, env_cpy);
	signal(SIGINT, ctrl_c_handler);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		/*it's the interactive mode*/
		errno = 2;
		prompt = PROMPT_MSG;
	}
	errno = 0;
	runShell(prompt, prog);
	return (0);
}


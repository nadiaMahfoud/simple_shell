#include "simple_shell.h"

/**
 * p_stdout - ThIs function takes a pointer to an array of characters
 * and writes the contents of the array to the stdout
 * @s: th pointer to an array of char
 * Return: how many bytes written (success) or -1 (failure)
 */

int p_stdout(char *s)
{
	return (write(STDOUT_FILENO, s, str_len(s)));
}

/**
 * p_stderr - tHis function is similar to p_stdout, but it writes
 * the contents of the array to the stderr instead of stdout
 * @s: The pointer to the array of characaters
 * Return: how many ybytes written (success) or -1 (failure)
 */

int p_stderr(char *s)
{
	return (write(STDERR_FILENO, s, str_len(s)));
}

/**
 * p_merr - ThiS function displays error msgs on the standard error output
 * @code: erroc code to print
 * @prog: a pointer to prog_data structure
 * Return: 0 (success) or -1(failure)
 */

int p_merr(int code, prog_data *prog)
{
	char buf[10] = {'\0'};
	/*buf is temporary buffer to convert prog->ctr_exe into strin*/

	l_to_str((long) prog->ctr_exe, buf, 10);
	if (code == 2 || code == 3)
	{
		p_stderr(prog->name);
		p_stderr(":");
		p_stderr(buf);
		p_stderr(":");
		p_stderr(prog->t[0]);
		p_stderr(code == 2 ? ": No such file or directory:"
				: "; No such process");
		p_stderr(prog->t[1]);
		p_stderr("\n");
	}
	else if (code == 127)
	{
		p_stderr(prog->name);
		p_stderr(":");
		p_stderr(buf);
		p_stderr(":");
		p_stderr(prog->cmd);
		p_stderr(": command is not found\n");
	}
	else if (code == 126)
	{
		p_stderr(prog->name);
		p_stderr(":");
		p_stderr(buf);
		p_stderr(":");
		p_stderr(prog->cmd);
		p_stderr(":Not executable\n");
	}
	return (0);
}

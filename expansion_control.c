#include "simple_shell.h"


/**
 * process_var - To expand variables
 * @prog: structure for the program's data.
 *
 * Return: nothing, but sets errno.
 */
void process_var(prog_data *prog)
{
	int n, m;
	char ligne[BUFFER_SIZE] = {0}, exp[BUFFER_SIZE] = {'\0'}, *tmp;

	if (prog->in == NULL)
		return;
	buffer_append(ligne, prog->in);
	for (n = 0; ligne[n]; n++)
		if (ligne[n] == '#')
			ligne[n--] = '\0';
	else if (ligne[n] == '$' && ligne[n + 1] == '?')
	{
		ligne[n] = '\0';
		l_to_str(errno, exp, 10);
		buffer_append(ligne, exp);
		buffer_append(ligne, prog->in + n + 2);
	}
	else if (ligne[n] == '$' && ligne[n + 1] == '$')
	{
		ligne[n] = '\0';
		l_to_str(getpid(), exp, 10);
		buffer_append(ligne, exp);
		buffer_append(ligne, prog->in + n + 2);
	}
	else if (ligne[n] == '$' && (ligne[n + 1] == ' ' || ligne[n + 1] == '\0'))
		continue;
	else if (ligne[n] == '$')
	{
		for (m = 1; ligne[n + m] && ligne[n + m] != ' '; m++)
			exp[m - 1] = ligne[n + m];
		tmp = update_environment_val(exp, prog);
		ligne[n] = '\0', exp[0] = '\0';
		buffer_append(exp, ligne + n + m);
		tmp ? buffer_append(ligne, tmp) : 1;
		buffer_append(ligne, exp);
	}
	if (!str_comp(prog->in, ligne, 0))
	{
		free(prog->in);
		prog->in = str_dup(ligne);
	}
}

/**
 * process_aliases - To process aliases
 * @prog: structure for the program's data.
 *
 * Return: nothing, but sets errno.
 */
void process_aliases(prog_data *prog)
{
	int n, m, was_exp = 0;
	char ligne[BUFFER_SIZE] = {0}, exp[BUFFER_SIZE] = {'\0'}, *tmp;

	if (prog->in == NULL)
		return;
	buffer_append(ligne, prog->in);
	for (n = 0; ligne[n]; n++)
	{
		for (m = 0; ligne[n + m] && ligne[n + m] != ' '; m++)
			exp[m] = ligne[n + m];
		exp[m] = '\0';
		tmp = retrieve_alias(prog, exp);
		if (tmp)
		{
			exp[0] = '\0';
			buffer_append(exp, ligne + n + m);
			ligne[n] = '\0';
			buffer_append(ligne, tmp);
			ligne[str_len(ligne)] = '\0';
			buffer_append(ligne, exp);
			was_exp = 1;
		}
		break;
	}
	if (was_exp)
	{
		free(prog->in);
		prog->in = str_dup(ligne);
	}
}

/**
 * buffer_append - To Appends a string at the end of the buffer.
 * @buf: The Buffer to be filled.
 * @s_to_add: String to be copied into the buffer.
 *
 * Return: Nothing, but sets errno.
 */
int buffer_append(char *buf, char *s_to_add)
{
	int len, n;

	len = str_len(buf); /* Get the current length of the buff */
	for (n = 0; s_to_add[n]; n++)
	{
		buf[len + n] = s_to_add[n];
	}
	buf[len + n] = '\0'; /* Add null-terminating at the end */
	return (len + n); /* Return the new length of the buffer */
}

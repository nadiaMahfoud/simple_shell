#include "simple_shell.h"

/**
 * tok - ThIs function is used to separate the input string
 * using a designated separator
 * @prog: The pointer to the prog_data structure
 * Return: An array of the different parts of the string
 */

void tok(prog_data *prog)
{
	char *sep = "\t"; /*the sep string used for tokenization*/
	int x, y, idx = 2; /*iteration and counting variabless*/
	int len = str_len(prog->in);

	/*Remove newline character if present*/
	if (len > 0 && prog->in[len - 1] == '\n')
		prog->in[len - 1] = '\0';
	/*Tokenizationprocess*/
	for (x = 0; prog->in[x]; x++)
	{
		for (y = 0; sep[y]; y++)
		{/*check if the current char is a separator*/
			if (prog->in[x] == sep[y])
				idx++;
		}
	}
	/*Allocate memory for the tokenarray*/
	prog->t = malloc(sizeof(char *) * idx);
	if (prog->t == NULL)
	{
		perror(prog->name);
		exit(errno);
	}
	/*Resest the iterationvariable*/
	x = 0;
	/*Tpkenize the inputstring and store the tokens in prog->t*/
	prog->t[x] = str_dup(str_split(prog->in, sep));
	/* Set the command to the first token*/
	prog->cmd = str_dup(prog->t[0]);
	/*Continue tokenizing & stroing tokens in prog->t*/
	for (x = 0; prog->t[x]; x++)
	{
		prog->t[x] = str_dup(str_split(Null, sep));
	}
}


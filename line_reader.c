#include "simple_shell.h"

/**
 * line_reader - Read one line of the standar input.
 * @prog: structure for the program's data
 *
 * Return: number of bytes read.
 */
int line_reader(prog_data *prog)
{
	ssize_t read_bytes, x = 0;
	char buffer[BUFFER_SIZE] = {'\0'};
	static char *command_array[10] = {NULL};
	static char operator_array[10] = {'\0'};

	/*Check both the logical operators */
	/*and if there are no more commands in the array */
	if (!command_array[0] || (operator_array[0] == '&' && errno != 0)
			|| (operator_array[0] == '|' && errno == 0))
	{
		/* Free the memory allocated if it exists */
		for (x = 0; command_array[x]; x++)
		{
			free(command_array[x]);
			command_array[x] = NULL;
		}
		/* Read from the file descriptor into the buffer */
		read_bytes = read(prog->fd, buffer, BUFFER_SIZE - 1);

		if (read_bytes == 0)
			return (-1);
		/* tokenize lines by '\n' or ';' */
		x = 0;

		do {
			command_array[x] = str_dup(str_split(x ? NULL : buffer, "\n;"));

			/* Check and tokenize for '&&' and '||' operators */
			x = process_logic_operators(command_array, x, operator_array);
		} while (command_array[x++]);
	}
	/* Obtain the next command 0 and remove it from the array */
	prog->in = command_array[0];
	for (x = 0; command_array[x]; x++)
	{
		command_array[x] = command_array[x + 1];
		operator_array[x] = operator_array[x + 1];
	}
	return (str_len(prog->in));
}

/**
* process_logic_operators - check and tokenize for '&&' and '||' operators
* @command_array: array of commands.
* @index: index in the command_array to be checked
* @operator_array: array of logical operators for each previous command
*
* Return: index of the last command in the command_array.
*/

int process_logic_operators(char *command_array[],
		int index, char operator_array[])
{
	char *tmp = NULL;
	int n;

	/* Check for the '&' character in the command line */
	for (n = 0; command_array[index] != NULL && command_array[index][n]; n++)
	{
		if (command_array[index][n] == '&' && command_array[index][n + 1] == '&')
		{
			/* tokenize the line when '&&' is found */
			tmp = command_array[index];
			command_array[index][n] = '\0';
			command_array[index] = str_dup(command_array[index]);
			command_array[index + 1] = str_dup(tmp + n + 2);
			index++;
			operator_array[index] = '&';
			free(tmp);
			n = 0;
		}
		if (command_array[index][n] == '|' && command_array[index][n + 1] == '|')
		{
			/* tokenize the line when '||' is found */
			tmp = command_array[index];
			command_array[index][n] = '\0';
			command_array[index] = str_dup(command_array[index]);
			command_array[index + 1] = str_dup(tmp + n + 2);
			index++;
			operator_array[index] = '|';
			free(tmp);
			n = 0;
		}
	}
	return (index);
}

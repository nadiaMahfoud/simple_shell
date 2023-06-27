#include "simple_shell.h"


/**
 * display_aliases - Add an alias, remove or show aliases
 * @prog: structure for the program's data
 * @alias_name: name of the alias to be printed
 * Return: 0 if success, or other number if it's declared in the argguments
 */

int display_aliases(prog_data *prog, char *alias_name)
{
	int n, m, alias_len;
	char buffer[250] = {'\0'};

	if (prog->aliases)
	{
		alias_len = str_len(alias_name);
		for (n = 0; prog->aliases[n]; n++)
		{
			if (!alias_name || (str_comp(prog->aliases[n], alias_name,
							alias_len) && prog->aliases[n][alias_len] == '='))
			{
				for (m = 0; prog->aliases[n][m]; m++)/* Cp the alias name into the buf */
				{
					buffer[m] = prog->aliases[n][m];
					if (prog->aliases[n][m] == '=')
						break; /* Stop copying when the '=' character is encountered */
				}
				buffer[m + 1] = '\0'; /* Null-terminate the buffer after the alias name */
				buffer_append(buffer, "'"); /* Append a single quote to the buffer */
				buffer_append(buffer, prog->aliases[n] + m + 1);/* Append the val */
				buffer_append(buffer, "'\n"); /* Append a newline char to the buffer */
				p_stdout(buffer); /* Print the buffer containing the alias information */
			}
		}
	}
	return (0);
}

/**
 * retrieve_alias - Add an alias, remove or show aliases
 * @prog: structure for the program's data
 * @name: name of the requested alias.
 * Return: 0 if success, or other number if it's declared in the arguments
 */

char *retrieve_alias(prog_data *prog, char *name)
{
	int x, alias_len;

	/* validate the arguments */
	if (name == NULL || prog->aliases == NULL)
		return (NULL);

	alias_len = str_len(name);

	for (x = 0; prog->aliases[x]; x++)
	{ /* Iterates through the environment and check for coincidence */
		if (str_comp(name, prog->aliases[x], alias_len)
				&& prog->aliases[x][alias_len] == '=')
		{ /* returns the value of the key NAME= when found */
			return (prog->aliases[x] + alias_len + 1);
		}
	}
	/* returns NULL if not found */
	return (NULL);
}

/**
 * define_alias - Add an alias or override an existing one
 * @alias_string: alias to be set in the form (name='value')
 * @prog: structure for the program's data
 * Return: 0 if success, or other number if it's declared in the arguments
 */
int define_alias(char *alias_string, prog_data *prog)
{
	int n, m;
	char buffer[250] = {'0'}, *tmp = NULL;

	/* validate the arguments */
	if (alias_string == NULL ||  prog->aliases == NULL)
		return (1);
	/* Iterates alias to find the '=' character */
	for (n = 0; alias_string[n]; n++)
		if (alias_string[n] != '=')
			buffer[n] = alias_string[n];
		else
			{ /* search if the value of the alias is another alias */
				tmp = retrieve_alias(prog, alias_string + n + 1);
				break;
			}
	/* Iterates through the alias list and check for coincidence */
	for (m = 0; prog->aliases[m]; m++)
		if (str_comp(buffer, prog->aliases[m], n)
				&& prog->aliases[m][n] == '=')
		{ /* if the alias already exists */
			free(prog->aliases[m]);
			break;
		}
	/* add the alias */
	if (tmp)
	{ /* if the alias already exists */
		buffer_append(buffer, "=");
		buffer_append(buffer, tmp);
		prog->aliases[m] = str_dup(buffer);
	}
	else /* if the alias does not exist */
		prog->aliases[m] = str_dup(alias_string);

	return (0);
}


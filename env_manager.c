#include "simple_shell.h"

/**
 * update_environment_val - To get the val of an environment variable
 * @cle: the environment var of interest
 * @prog: structure of the program's prog
 * Return: a pointer to the value of the var or NULL if it doesn't exist
 */
char *update_environment_val(char *cle, prog_data *prog)
{
	int n, key_len = 0;

	/* validates the args */
	if (cle == NULL || prog->env_cpy == NULL)
		return (NULL);
	/* obtains the length of the var requested */
	key_len = str_len(cle);
	for (n = 0; prog->env_cpy[n]; n++)
	{ /* Iterates through the environ and checks for coincidence of the name */
		if (str_comp(cle, prog->env_cpy[n], key_len)
				&& prog->env_cpy[n][key_len] == '=')
			return (prog->env_cpy[n] + key_len + 1);

	}
	/* returns NULL if didn't find it */
	return (NULL);
}

/**
 * set_environment - overwrites the value of the environment var
 * or create it if it doesn't exist.
 * @cle: the name of the var to set
 * @val: the new value
 * @prog: structure of the program's prog
 * Return: 1 if the parameters are NULL, 2 if there is an erroror 0 if sucess.
 */
int set_environment(char *cle, char *val, prog_data *prog)
{
	int n, key_len = 0, new_key = 1;

	/* validate the args */
	if (cle == NULL || val == NULL || prog->env_cpy == NULL)
		return (1);
	/* obtains the length of the var requested */
	key_len = str_len(cle);

	for (n = 0; prog->env_cpy[n]; n++)
	{
		if (str_comp(cle, prog->env_cpy[n], key_len) &&
				prog->env_cpy[n][key_len] == '=')
		{
			new_key = 0;
			free(prog->env_cpy[n]);
			break;
		}
	}
	/* make a string of the form cle = val */
	prog->env_cpy[n] = str_cat(str_dup(cle), "=");
	prog->env_cpy[n] = str_cat(prog->env_cpy[n], val);
	if (new_key)
		prog->env_cpy[n + 1] = NULL;

	return (0);
}

/**
 * delete_environment_key - To remove a key from the environment
 * @cle: the key to remove
 * @prog: the structure of the program's data
 * Return: 1 if the key was removed, 0 if the key does not exist;
 */
int delete_environment_key(char *cle, prog_data *prog)
{
	int n, key_len = 0;

	/* validate the args */
	if (cle == NULL || prog->env_cpy == NULL)
		return (0);
	/* obtains the length of the var requested */
	key_len = str_len(cle);
	for (n = 0; prog->env_cpy[n]; n++)
	{ /* iterates through the environ and checks for coincidences */
		if (str_comp(cle, prog->env_cpy[n], key_len) &&
				prog->env_cpy[n][key_len] == '=')
		{
			free(prog->env_cpy[n]);
			n++;
			for (; prog->env_cpy[n]; n++)
			{
				prog->env_cpy[n - 1] = prog->env_cpy[n];
			}
			/* put the NULL value at the new end of the list */
			prog->env_cpy[n - 1] = NULL;
			return (1);
		}
	}
	return (0);
}

/**
 * show_environment - prints the current environ
 * @prog: structure for the program's data
 * Return: nothing
 */
void show_environment(prog_data *prog)
{
	int j;

	for (j = 0; prog->env_cpy[j]; j++)
	{
		p_stdout(prog->env_cpy[j]);
		p_stdout("\n");
	}
}

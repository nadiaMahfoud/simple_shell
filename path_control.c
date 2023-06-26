#include "simple_shell.h"

/**
 * find_exec - to find a program in path
 * @prog: a pointer to the program's data
 * Return: 0 if success, errcode otherwise
 */
int find_exec(prog_data *prog)
{
	int x = 0, code = 0;
	char **direc;
	char *tmp;

	if (!prog->cmd)
		return (2);
	/* if it's a full path or an executable in the same path */
	if (prog->cmd[0] == '/' || prog->cmd[0] == '.')
		return (path_valid(prog->cmd));
	free(prog->t[0]);
	prog->t[0] = str_cat("/", prog->cmd);
	if (!prog->t[0])
		return (2);
	direc = tok_environment_path(prog);/* search in the PATH */
	if (!direc || !direc[0])
	{
		errno = 127;
		return (127);
	}
	for (x = 0; direc[x]; x++)
	{/* appends the function_name to path */
		tmp = str_cat(direc[x], prog->t[0]);
		code = path_valid(tmp);
		if (code == 0 || code == 126)
		{/* the file is found, isn't a directory and has execute permisions*/
			errno = 0;
			free(prog->t[0]);
			prog->t[0] = tmp;
			free_ptrs(direc);
			return (code);
		}
		free(tmp);
	}
	free(prog->t[0]);
	prog->t[0] = NULL;
	free_ptrs(direc);
	return (code);
}
/**
 * tok_environment_path - tokenize the path in directories
 * @prog: a pointer to the program's data
 * Return: array of path directories
 */
char **tok_environment_path(prog_data *prog)
{
	int x = 0;
	int count_direct = 2;
	char **tokens = NULL;
	char *PATH;

	/* get the PATH value*/
	PATH = update_environment_val("PATH", prog);
	if ((PATH == NULL) || PATH[0] == '\0')
	{/*path not found*/
		return (NULL);
	}
	PATH = str_dup(PATH);
	/* find the number of directories in the PATH */
	for (x = 0; PATH[x]; x++)
	{
		if (PATH[x] == ':')
			count_direct++;
	}
	/* reserve space for the array of pointers */
	tokens = malloc(sizeof(char *) * count_direct);
	/*tokenize and duplicate each token of path*/
	x = 0;
	tokens[x] = str_dup(str_split(PATH, ":"));
	while (tokens[x++])
	{
		tokens[x] = str_dup(str_split(NULL, ":"));
	}
	free(PATH);
	PATH = NULL;
	return (tokens);
}

/**
 * path_valid - checks if file exists , if it isn't a dairectory and
 * if it has execution permisions.
 * @path: pointer to the full file name
 * Return: 0 on success, or error code if it exists.
 */
int path_valid(char *path)
{
	struct stat s;

	if (stat(path, &s) != -1)
	{
		if (S_ISDIR(s.st_mode) ||  access(path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	/*if not exist the file*/
	errno = 127;
	return (127);
}

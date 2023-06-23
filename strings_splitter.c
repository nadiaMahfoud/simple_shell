#include "simple_shell.h"

/**
 * str_split - this function splits the strings using delimiters
 * @src: The pointer to the data we receive from line_reader function
 * @sep: the pointer to the separator or delimiter character
 * Return: the Token pointer after modifyingthe string
 */

char *str_split(char *src, char *sep)
{
	int iter; /*Iterator variable for loopingthrough delimiter character*/
	static char *s; /* to track the position in the source string*/
	char *tok; /* pointer to the tokenbeingg extracted*/

	if (src != NULL)
		s = src;
	/*Find the first occurence of a delimiter*/
	while (*s != '\0')
	{
		for (iter = 0; sep[iter] != '\0'; iter++)
		{
			if (*s == sep[iter])
				break;
		}
		if (sep[iter] == '\0')
			break;
		s++;
	}
	tok = s;
	if (*tok == '\0')
		return (NULL);
	/*Find subsequent occurences of ddelimiters*/
	while (*s != '\0')
	{
		for (iter = 0; sep[iter] != '\0'; iter++)
		{
			if (*s == sep[iter])
			{
				*s = '\0';
				s++;
				return (tok);
			}
		}
		s++;
	}
	return (tok);
}


#include "simple_shell.h"

/**
 * str_comp - ThiS function compares the characters of two strings as input
 * @str1: Our first string
 * @str2: Ous second string
 * @cmp: represents the num of char to compare, with
 * Return: 1(equal strs), or 0 (different stsrs)
 */

int str_comp(char *str1, char *str2, int cmp)
{
	int idx;

	if (str1 == NULL && str2 == NULL)
		return (1);
	if (str1 == NULL || str2 == NULL)
		return (0);
	if (cmp == 0) /* undicating an unlimited number of characters*/
	{
		if (str_len(str1) != str_len(str2))
			return (0);
		for (idx = 0; str1[idx]; idx++)
		{
			if (str1[idx] != str2[idx])
				return (0);
		}
		return (1);
	}
	else /*if a cmp of characters needs to be compared*/
	{
		for (idx = 0; idx < cmp; idx++)
		{
			if (str1[idx] != str2[idx])
				return (0);
		}
		return (1);
	}
}

/**
 * str_len - ThiS function returns the length of a string
 * @str: The pointer to the input string
 * Return: the lenght of the string str
 */

int str_len(char *str)
{
	int i = 0;

	if (str == NULL)
		return (0);
	while (str[i++] != '\0')
	{
	}

	return (--i);
}

/**
 * str_cat - This function concatentaes two strings
 * @dest: the destination str to be concatenated
 * @src: The source string string to be concatenated
 * Return: ThE pointer to the array of the resultant string
 */

char *str_cat(char *dest, char *src)
{
	int dest_len = 0, src_len = 0;
	int i = 0, j = 0;
	char *res;

	if (dest == NULL)
		dest = "";
	/*Lenght of the destination string*/
	dest_len = str_len(dest);
	if (src == NULL)
		src = "";
	/*Length of the source string*/
	src_len = str_len(src);
	/*Allocate memory for the resukting string*/
	res = malloc(sizeof(char) * (dest_len + src_len + 1));
	if (res == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	/*Copy the characters of the dest str to the res*/
	for (dest_len = 0; dest[dest_len] != '\0'; dest_len++)
		res[dest_len] = dest[dest_len];
	free(dest);
	/*Copy the char of the src str to the res, starting after dest str*/
	for (src_len = 0; src[src_len] != '\0'; src_len++)
	{
		res[dest_len] = src[src_len];
		dest_len++;
	}

	/*Adding the null_terminator at the end of res*/
	res[dest_len] = '\0';

	return (res);
}

/**
 * str_rev - ThiS function reverses a string
 * @s: thE string to be reversed
 * Return: Void
 */

void str_rev(char *s)
{
	char rev_str;
	int a, x = 0;

	a = str_len(s) - 1;
	while (x < a)
	{
		rev_str = s[x];
		s[x++] = s[a];
		s[a--] = rev_str;
	}
}

/**
 * str_dup - tHis function returns a pointer to a newly allocated
 * space in memory, which contains a copy of the string given as a parameter
 * @str: Our string to be copied
 * Return: The duplicated string (on success) or NULL (if str is null
 * or if insufficient memory is available))
 */

char *str_dup(char *str)
{
	int x = 0, size = 0;
	char *dup;

	if (str == 0)
		return (0);
	size = str_len(str) + 1;
	dup = malloc(sizeof(char) * size);
	if (dup == 0)
	{
		errno = ENOMEM; /* system is out of memmory*/
		perror("Error");
		return (NULL);
	}
	else
	{
		for (; x < size; x++)
			dup[x] = str[x];
	}
	return (dup);
}

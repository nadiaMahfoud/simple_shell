#include "simple_shell.h"

/**
 * str_to_int - THiS function converts string s to an integer value
 * @s: The pointer to strng
 * Return: The converted integer (success) or 0 (failure)
 */
int str_to_int(char *s)
{
	unsigned int numb = 0;
	int ind = 1;

	while (!('0' <= *s && *s <= '9') && *s != '\0')
	{
		if (*s == '-')
			ind = -1 * ind;
		if (*s == '+')
			ind = 1 * ind;
		s++;
	}
	while ('0' <= *s && *s <= '9' && *s != '\0')
	{
		numb = (numb * 10) + (*s - '0');
		s++;
	}
	return (numb * ind);
}
/**
 * char_occ - ThIs function counts the occurences of a specific character
 * in a given string
 * @str: The string pointer
 * @a: the character to search for its occurences
 * Return: how many occurences of the character.
 */
int char_occ(char *str, char *a)
{
	int y = 0, o = 0;

	while (str[y])
	{
		if (str[y] == *a)
			o++;
		y++;
	}
	return (o);
}

/**
 * l_to_str - This function converts a long int to a String
 * @numb: tThe long integer to convert to a string.
 * @str: storage buffer of the converted number as String.
 * @b: the base to convert the long int numbner to.
 * Return: void.
 */

void l_to_str(long numb, char *str, int b)
{
	long q = numb;
	char chars[] = {"0123456789abcdef"};
	int x = 0, toNeg = 0;

	if (q == 0)
		str[x++] = '0';
	if (str[0] == '-')
		toNeg = 1;
	while (q)
	{
		if (q < 0)
			str[x++] = chars[-(q % b)];
		else
			str[x++] = chars[q % b];
		q = q / b;
	}
	if (toNeg)
		str[x++] = '-';

	str[x] = '\0';
	str_rev(str);
}

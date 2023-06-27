#include "simpshell.h"

/**
 * interactive - if shell is in interactive mode, returns true
 * @info: structure address information
 * Return: 1 if in interactive mode, 0 if not
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - this checks if a character is a delimeter
 * @c: the character to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if not
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - this checks if a character is an alphabet
 * @c: The character to check
 * Return: 1 if c is an alphabet, 0 if not
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - this converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if there are no numbers in the string, the integer if otherwise
 */

int _atoi(char *s)
{
	int k, chek = 1, site = 0, result;
	unsigned int answer = 0;

	for (k = 0; s[k] != '\0' && site != 2; k++)
	{
		if (s[k] == '-')
			chek *= -1;

		if (s[k] >= '0' && s[k] <= '9')
		{
			site = 1;
			answer *= 10;
			answer += (s[k] - '0');
		}
		else if (site == 1)
			site = 2;
	}

	if (chek == -1)
		result = -answer;
	else
		result = answer;

	return (result);
}

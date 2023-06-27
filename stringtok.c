#include "simpshell.h"

/**
 * **strtow - this will split a string into words and ignore delimeters
 * @str: the string input
 * @d: the delimeter string
 * Return: pointer to an array of strings, if failed, NULL
 */

char **strtow(char *str, char *d)
{
	int a, b, c, m, drew = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!is_delim(str[a], d) && (is_delim(str[a + 1], d) || !str[a + 1]))
			drew++;

	if (drew == 0)
		return (NULL);
	s = malloc((1 + drew) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < drew; b++)
	{
		while (is_delim(str[a], d))
			a++;
		c = 0;
		while (!is_delim(str[a + c], d) && str[a + c])
			c++;
		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < c; m++)
			s[b][m] = str[a++];
		s[b][m] = 0;
	}
	s[b] = NULL;
	return (s);
}

/**
 * **strtow2 - this will split a string into words
 * @str: the string input
 * @d: the delimeter
 * Return: pointer to an array of strings, if failed then NULL
 */

char **strtow2(char *str, char d)
{
	int a, b, c, m, drew = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (a = 0; str[a] != '\0'; a++)
		if ((str[a] != d && str[a + 1] == d) ||
				    (str[a] != d && !str[a + 1]) || str[a + 1] == d)
			drew++;
	if (drew == 0)
		return (NULL);
	s = malloc((1 + drew) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < drew; b++)
	{
		while (str[a] == d && str[a] != d)
			a++;

		c = 0;
		while (str[a + c] != d && str[a + c] && str[a + c] != d)
			c++;
		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < c; m++)
			s[b][m] = str[a++];
		s[b][m] = 0;
	}
	s[b] = NULL;
	return (s);
}

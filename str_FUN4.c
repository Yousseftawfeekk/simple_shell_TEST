#include "shell.h"

/**
 * **strtow2 - splits a string into words
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **splitstr1(char *str, char del)
{
	int i, j, k, m, wordnums = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != del && str[i + 1] == del) ||
				    (str[i] != del && !str[i + 1]) || str[i + 1] == del)
			wordnums++;
	if ((wordnums) == 0)
		return (NULL);
	s = malloc((1 + wordnums) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < wordnums; j++)
	{
		while (str[i] == del && str[i] != del)
			i++;
		k = 0;
		while (str[i + k] != del && str[i + k] && str[i + k] != del)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;

	return (s);
}

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @del: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **splitstr2(char *str, char *del)
{
	int i, j, k, m, wordnums = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	
	if (!del)
		del = " ";
	
	for (i = 0; str[i] != '\0'; i++)
		if (!check_delim(str[i], del) && (check_delim(str[i + 1], del) || !str[i + 1]))
			wordnums++;

	if (wordnums == 0)
		return (NULL);
	
	s = malloc((wordnums + 1) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < wordnums; j++)
	{
		while (check_delim(str[i], del))
			i++;
		k = 0;
		while (!check_delim(str[i + k], del) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;

	return (s);
}

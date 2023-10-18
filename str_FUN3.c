#include "shell.h"

/**
 **_strNcpy - copies a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@Nchar: the number of characters to be copied
 *
 * Return: the concatenated string
 */

char *_strNcpy(char *dest, char *src, int Nchar)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < Nchar - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < Nchar)
	{
		j = i;
		while (j < Nchar)
		{
			dest[j] = '\0';
			j++;
		}
	}

	return (s);
}

/**
 **_strchr - locates a character in a string
 *@s: the string to be parsed
 *@C: the character to look for
 *Return: (s) a pointer to the memory area s
 */

char *_strchr(char *s, char C)
{
	do {
		if (*s == C)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

/**
 **_strNcat - concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@N: the amount of bytes to be maximally used
 *Return: the concatenated string
 */

char *_strNcon(char *dest, char *src, int N)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < N)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < N)
		dest[i] = '\0';

	return (s);
}

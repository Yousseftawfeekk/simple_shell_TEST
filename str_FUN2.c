#include "shell.h"

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _putchar(char c)
{
	static int i;
	static char buff[WRITE_BUFF_SIZE];

	if (c == BUFF_FLUSH || i >= WRITE_BUFF_SIZE)
	{
		write(1, buff, i);
		i = 0;
	}
	if (c != BUFF_FLUSH)
		buff[i++] = c;
	return (1);
}

/**
 * _puts - prints an input string
 * @str: the string printed
 *
 * Return: void
 */

void _puts(char *str)
{
	int s = 0;

	if (!str)
		return;
	while (str[s] != '\0')
	{
		_putchar(str[s]);
		s++;
	}
}

/**
 * str_dup - duplicates a string
 * @str: the string we wantv to duplicate
 *
 * Return: pointer to duplicated string
 */

char *str_dup(const char *str)
{
	int len = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	for (len++; len--;)
		ret[len] = *--str;
	return (ret);
}

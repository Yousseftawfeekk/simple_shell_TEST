#include "shell.h"

/**
 * _eputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int error_putchar(char C)
{
	static int i;
	static char buff[WRITE_BUFF_SIZE];

	if (C == BUFF_FLUSH || i >= WRITE_BUFF_SIZE)
	{
		write(2, buff, i);
		i = 0;
	}

	if (C != BUFF_FLUSH)
		buff[i++] = C;

	return (1);
}


/**
 * _eputs - prints an input string
 * @str: the string to be printed
 *
 * Return: void
 */

void error_puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		error_putchar(str[i]);
		i++;
	}
}



/**
 * _putfd - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int write_fileDes(char C, int fileDes)
{
	static int i;
	static char buff[WRITE_BUFF_SIZE];

	if (C == BUFF_FLUSH || i >= WRITE_BUFF_SIZE)
	{
		write(fileDes, buff, i);
		i = 0;
	}

	if (C != BUFF_FLUSH)
		buff[i++] = C;

	return (1);
}

/**
 * _putsfd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */

int puts_fileDes(char *str, int fileDes)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += write_fileDes(*str++, fileDes);
	}
	
	return (i);
}

/**
 * comment_eliminate - function replaces first instance of '#' with '\0'
 * @buff: address of the string to modify
 *
 * Return: void;
 */

void comment_eliminate(char *buff)
{
	int i;

	for (i = 0; buff[i] != '\0'; i++)
		if (buff[i] == '#' && (!i || buff[i - 1] == ' '))
		{
			buff[i] = '\0';
			break;
		}
}

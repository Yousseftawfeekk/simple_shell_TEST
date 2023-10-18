#include "shell.h"

/**
 * check_alpha - checks for alphabetic character
 * @c: The character to input
 * 
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int check_alpha(int C)
{
	if ((C >= 'a' && C <= 'z') || (C >= 'A' && C <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * check_delim - checks if character is a delimeter
 * @C: the char to check
 * @del: the delimeter string
 * 
 * Return: 1 if true, 0 if false
 */

int check_delim(char C, char *del)
{
	while (*del)
		if (*del++ == C)
			return (1);

	return (0);
}

/**
 * interact_mood - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */

int interact_mood(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfileDes <= 2);
}

/**
 * str_int - converts a string to an integer
 * @str: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int str_int(char *str)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; str[i] != '\0' && flag != 2; i++)
	{
		if (str[i] == '-')
			sign *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

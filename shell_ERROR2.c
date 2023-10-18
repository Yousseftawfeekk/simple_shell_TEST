#include "shell.h"

/**
 * errstr_int - converts a string to an integer
 * @str: the string to be converted
 *
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int errstr_int(char *str)
{
	int i = 0;
	unsigned long int final = 0;

	if (*str == '+')
		str++;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			final *= 10;
			final += (s[i] - '0');
			if (final > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (final);
}

/**
 * print_error - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: void
 */
void error_output(info_t *info, char *errstr)
{
	error_puts(info->program_name);
	error_puts(": ");
	print_decimal(info->count_line, STDERR_FILENO);
	error_puts(": ");
	error_puts(info->argv[0]);
	error_puts(": ");
	error_puts(errstr);
}

/**
 * print_d - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */

int print_decimal(int input, int fileDes)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fileDes == STDERR_FILENO)
		__putchar = error_putchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */

char *int_str(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;

	return (ptr);
}

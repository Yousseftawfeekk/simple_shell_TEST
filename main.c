#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */

int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fileDes = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fileDes)
			: "r" (fileDes));

	if (ac == 2)
	{
		fileDes = open(av[1], O_RDONLY);
		if (fileDes == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				error_puts(av[0]);
				error_puts(": 0: Can't open ");
				error_puts(av[1]);
				error_putchar('\n');
				error_putchar(BUFF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfileDes = fileDes;
	}
	enviorn_listPOP(info);
	read_SHELLhistory(info);
	shell_loop(info, av);
	return (EXIT_SUCCESS);
}

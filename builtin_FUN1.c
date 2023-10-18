#include "shell.h"

/**
 * myshell_exit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 *
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */

int myshell_exit(info_t *info)
{
	int checkExit;

	if (info->argv[1])
	{
		checkExit = errstr_int(info->argv[1]);
		if (checkExit == -1)
		{
			info->status = 2;
			error_output(info, "Illegal number: ");
			error_puts(info->argv[1]);
			error_putchar('\n');
			return (1);
		}
		info->err_num = errstr_int(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * mychange_dir - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 *
 * Return: Always 0
 */

int mychange_dir(info_t *info)
{
	char *s, *dir, buffer[1024];
	int changedir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");

	if (!info->argv[1])
	{
		dir = get_MYenviornment(info, "HOME=");
		if (!dir)
			changedir_ret =
				chdir((dir = get_MYenviornment(info, "PWD=")) ? dir : "/");
		else
			changedir_ret = chdir(dir);
	}
	else if (str_cmp(info->argv[1], "-") == 0)
	{
		if (!get_MYenviornment(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(get_MYenviornment(info, "OLDPWD=")), _putchar('\n');
		changedir_ret =
			chdir((dir = get_MYenviornment(info, "OLDPWD=")) ? dir : "/");
	}
	else
		changedir_ret = chdir(info->argv[1]);
	if (changedir_ret == -1)
	{
		error_output(info, "can't cd to ");
		error_puts(info->argv[1]), error_putchar('\n');
	}
	else
	{
		set_MYenviron(info, "OLDPWD", get_MYenviornment(info, "PWD="));
		set_MYenviron(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 *
 *  Return: Always 0
 */

int myshell_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array);

	return (0);
}

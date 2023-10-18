#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */

int shell_loop(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clearMYinfo(info);
		if (interact_mood(info))
			_puts("$ ");
		error_putchar(BUFF_FLUSH);
		r = input_get(info);
		if (r != -1)
		{
			setMYinfo(info, av);
			builtin_ret = builtin_FIND(info);
			if (builtin_ret == -1)
				cmd_FIND(info);
		}
		else if (interact_mood(info))
			_putchar('\n');
		freeMYinfo(info, 0);
	}
	write_SHELLhistory(info);
	freeMYinfo(info, 1);
	if (!interact_mood(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *	0 if builtin executed successfully,
 *	1 if builtin found but not successful,
 *	2 if builtin signals exit()
 */

int builtin_FIND(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", myshell_exit},
		{"env", MYenvironment_Print},
		{"help", myshell_help},
		{"history", display_myhistory},
		{"setenv", set_myNEW_environ},
		{"unsetenv", unset_MYenv},
		{"cd", mychange_dir},
		{"alias", man_Alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (str_cmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->count_line++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */

void cmd_FIND(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->count_line++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!check_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = MYpath(info, get_MYenviornment(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		CMD_fork(info);
	}
	else
	{
		if ((interact_mood(info) || get_MYenviornment(info, "PATH=")
					|| info->argv[0][0] == '/') && check_cmd(info, info->argv[0]))
			CMD_fork(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			error_output(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void CMD_fork(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environment(info)) == -1)
		{
			freeMYinfo(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				error_output(info, "Permission denied\n");
		}
	}
}

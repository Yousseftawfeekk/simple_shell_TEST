#include "shell.h"

/**
 * clearMYinfo - initializes info_t struct
 * @info: struct address
 * 
 * Return: void
 */

void clearMYinfo(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 * 
 * Return: void
 */

void setMYinfo(info_t *info, char **av)
{
	int i = 0;

	info->program_name = av[0];
	if (info->arg)
	{
		info->argv = splitstr2(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = str_dup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		alias_Replace(info);
		var_Replace(info);
	}
}

/**
 * free_info - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 * 
 * Return: void
 */

void freeMYinfo(info_t *info, int all)
{
	free_string(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buff)
			free(info->arg);
		if (info->env)
			mylistFREE(&(info->env));
		if (info->history)
			mylistFREE(&(info->history));
		if (info->alias)
			mylistFREE(&(info->alias));
		free_string(info->environ);
			info->environ = NULL;
		ptr_free((void **)info->cmd_buff);
		if (info->readfileDes > 2)
			close(info->readfileDes);
		_putchar(BUFF_FLUSH);
	}
}

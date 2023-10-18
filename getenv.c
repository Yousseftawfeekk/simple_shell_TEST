#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environment(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = listStr(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 *
 *   Return: 1 on delete, 0 otherwise
 */

int unset_enviorn(info_t *info, char *varenv)
{
	list_t *node = info->env;
	size_t i = 0;
	char *ptr;

	if (!node || !varenv)
		return (0);

	while (node)
	{
		ptr = startWith(node->str, varenv);
		if (ptr && *ptr == '=')
		{
			info->env_changed = NodeRemove(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	
    return (info->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 * 
 *  Return: Always 0
 */

int set_MYenviron(info_t *info, char *varenv, char *value)
{
	char *buff = NULL;
	list_t *node;
	char *ptr;

	if (!varenv || !value)
		return (0);

	buff = malloc(str_len(varenv) + str_len(value) + 2);
	if (!buff)
		return (1);
	
    str_cpy(buff, varenv);
	str_con(buff, "=");
	str_con(buff, value);
	node = info->env;
	while (node)
	{
		ptr = startWith(node->str, varenv);
		if (ptr && *ptr == '=')
		{
			free(node->str);
			node->str = buff;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	node_endADD(&(info->env), buff, 0);
	free(buff);
	info->env_changed = 1;
	
    return (0);
}

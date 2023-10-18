#include "shell.h"

/**
 * display_myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * 
 *  Return: Always 0
 */

int display_myhistory(info_t *info)
{
	mylistPrint(info->history);
	return (0);
}

/**
 * alias_UNset - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */

int alias_UNset(info_t *info, char *str)
{
	char *ptr, C;
	int ret;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	C = *ptr;
	*ptr = 0;
	ret = NodeRemove(&(info->alias),
		mynode_index(info->alias, mynode_starts(info->alias, str, -1)));
	*ptr = C;
	return (ret);
}

/**
 * alias_SET - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */

int alias_SET(info_t *info, char *str)
{
	char *ptr;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (alias_UNset(info, str));

	alias_UNset(info, str);
	return (node_endADD(&(info->alias), str, 0) == NULL);
}

/**
 * alias_Print - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int alias_Print(list_t *node)
{
	char *ptr = NULL, *alias = NULL;

	if (node)
	{
		ptr = _strchr(node->str, '=');
		for (alias = node->str; alias <= ptr; alias++)
		_putchar(*alias);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * man_Alias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *
 *   Return: Always 0
 */


int man_Alias(info_t *info)
{
	int i = 0;
	char *ptr = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			alias_Print(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		ptr = _strchr(info->argv[i], '=');
		if (ptr)
			alias_SET(info, info->argv[i]);
		else
			alias_Print(mynode_starts(info->alias, info->argv[i], '='));
	}

	return (0);
}

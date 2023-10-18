#include "shell.h"

/**
 * check_BUFFchain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buff: the char buffer
 * @ptr: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */

int check_BUFFchain(info_t *info, char *buff, size_t *ptr)
{
	size_t D = *ptr;

	if (buff[D] == '|' && buff[D + 1] == '|')
	{
		buff[D] = 0;
		D++;
		info->cmd_buff_type = CMD_OR;
	}
	else if (buff[D] == '&' && buff[D + 1] == '&')
	{
		buff[D] = 0;
		D++;
		info->cmd_buff_type = CMD_AND;
	}
	else if (buff[D] == ';')
	{
		buff[D] = 0;
		info->cmd_buff_type = CMD_CHAIN;
	}
	else
		return (0);

	*ptr = D;
	return (1);
}

/**
 * check_ischain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buff: the char buffer
 * @ptr: address of current position in buf
 * @i: starting position in buf
 * @buff_len: length of buf
 *
 * Return: Void
 */

void check_ischain(info_t *info, char *buff, size_t *ptr, size_t i, size_t buff_len)
{
	size_t D = *ptr;

	if (info->cmd_buff_type == CMD_AND)
	{
		if (info->status)
		{
			buff[i] = 0;
			D = buff_len;
		}
	}
	if (info->cmd_buff_type == CMD_OR)
	{
		if (!info->status)
		{
			buff[i] = 0;
			D = buff_len;
		}
	}

	*ptr = D;
}

/**
 * alias_Replace - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */

int alias_Replace(info_t *info)
{
	int i;
	list_t *node;
	char *ptr;

	for (i = 0; i < 10; i++)
	{
		node = mynode_starts(info->alias, info->argv[0], '=');
		if (!node)
			return (0);

	free(info->argv[0]);
	ptr = _strchr(node->str, '=');

	if (!ptr)
		return (0);

	ptr = str_dup(ptr + 1);

	if (!ptr)
		return (0);

	info->argv[0] = ptr;
	}
	return (1);
}

/**
 * vars_Replace - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */

int var_Replace(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!str_cmp(info->argv[i], "$?"))
		{
			string_Repalce(&(info->argv[i]),
					str_dup(int_str(info->status, 10, 0)));
			continue;
		}
		if (!str_cmp(info->argv[i], "$$"))
		{
			string_Repalce(&(info->argv[i]),
					str_dup(int_str(getpid(), 10, 0)));
			continue;
		}
		node = mynode_starts(info->env, &info->argv[i][1], '=');
		if (node)
		{
			string_Repalce(&(info->argv[i]),
					str_dup(_strchr(node->str, '=') + 1));
			continue;
		}
		string_Repalce(&info->argv[i], str_dup(""));

	}
	return (0);
}

/**
 * string_Replace - replaces string
 * @oldStr: address of old string
 * @newStr: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */

int string_Repalce(char **oldStr, char *newStr)
{
	free(*oldStr);
	*oldStr = newStr;

	return (1);
}

#include "shell.h"

/**
 * mylistLength - determines length of linked list
 * @firsNode: pointer to first node
 *
 * Return: size of list
 */

size_t mylistLength(const list_t *firstNode)
{
	size_t i = 0;

	while (firstNode)
	{
		firstNode = firstNode->next;
		i++;
	}
	return (i);
}

/**
 * listStr - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */

char **listStr(list_t *head)
{
	list_t *node = head;
	size_t i = mylistLength(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);

	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);

	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(str_len(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = str_cpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * mylistprint- prints all elements of a list_t linked list
 * @firstNode: pointer to first node
 *
 * Return: size of list
 */

size_t mylistPrint(const list_t *firstNode)
{
	size_t i = 0;

	while (firstNode)
	{
		_puts(int_str(firstNode->node_num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(firstNode->str ? firstNode->str : "(nil)");
		_puts("\n");
		firstNode = firstNode->next;
		i++;
	}

	return (i);
}

/**
 * mynode_strats - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node o
 */

list_t *mynode_starts(list_t *node, char *strtext, char C)
{
	char *ptr = NULL;

	while (node)
	{
		ptr = startWith(node->str, strtext);
		if (ptr && ((C == -1) || (*ptr == C)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * mynode_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */

ssize_t mynode_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);

		head = head->next;
		i++;
	}
	return (-1);
}

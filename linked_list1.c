#include "shell.h"

/**
 * my_node - adds a node to the start of the list
 * @old_head: address of pointer to head node
 * @str: str field of node
 * @node: node index used by history
 *
 * Return: size of list
 */

list_t *my_node(list_t **old_head, const char *str, int node)
{
	list_t *new_Head;

	if (!old_head)
		return (NULL);
	new_Head = malloc(sizeof(list_t));
	if (!new_Head)
		return (NULL);
	
    fills_memory((void *)new_Head, 0, sizeof(list_t));
	new_Head->node_num = node;
	if (str)
	{
		new_Head->str = str_dup(str);
		if (!new_Head->str)
		{
			free(new_Head);
			return (NULL);
		}
	}
	new_Head->next = *old_head;
	*old_head = new_Head;
	
    return (new_Head);
}

/**
 * node_endADD - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *node_endADD(list_t **head, const char *str, int num)
{
	list_t *newNode, *node;

	if (!head)
		return (NULL);

	node = *head;
	newNode = malloc(sizeof(list_t));
	if (!newNode)
		return (NULL);
	
    fills_memory((void *)newNode, 0, sizeof(list_t));
	newNode->node_num = num;
	if (str)
	{
		newNode->str = str_dup(str);
		if (!newNode->str)
		{
			free(newNode);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = newNode;
	}
	else
		*head = newNode;
	
    return (newNode);
}

/**
 * print_list_str - prints only the str element of a list_t linked list
 * @firstNode: pointer to first node
 *
 * Return: size of list
 */

size_t mylist_StrPrint(const list_t *firstNode)
{
	size_t i = 0;

	while (firstNode)
	{
		_puts(firstNode->str ? firstNode->str : "(nil)");
		_puts("\n");
		firstNode = firstNode->next;
		i++;
	}
	return (i);
}

/**
 * nodeRemove - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */

int NodeRemove(list_t **head, unsigned int Nodeindex)
{
	list_t *node, *last_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!Nodeindex)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == Nodeindex)
		{
			last_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		last_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * mylistFREE - frees all nodes of a list
 * @head_address: address of pointer to head node
 *
 * Return: void
 */

void mylistFREE(list_t **head_address)
{
	list_t *node, *next_node, *head;

	if (!head_address || !*head_address)
		return;
	head = *head_address;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_address = NULL;
}

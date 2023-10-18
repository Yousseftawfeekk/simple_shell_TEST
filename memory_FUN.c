#include "shell.h"

/**
 * _realloc - reallocates a block of memory
 * @Old_ptr: pointer to previous malloc'ated block
 * @Old_memory: byte size of previous block
 * @New_memory: byte size of new block
 *
 * Return: pointer to a new memory allocation.
 */

void *New_alloc(void *Old_ptr, unsigned int Old_Memory, unsigned int New_Memory)
{
	char *New_ptr;

	if (!Old_ptr)
		return (malloc(New_Memory));

	if (!New_Memory)
		return (free(Old_ptr), NULL);

	if (New_Memory == Old_Memory)
		return (Old_ptr);

	New_ptr = malloc(New_Memory);

	if (!New_ptr)
		return (NULL);

	Old_Memory = Old_Memory < New_Memory ? Old_Memory : New_Memory;
	while (Old_Memory--)
		New_ptr[Old_Memory] = ((char *)Old_ptr)[Old_Memory];

	free(Old_ptr);
	return (New_ptr);
}


/**
 * ptr_free - frees a pointer and NULLs the address
 * @address: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */

int ptr_free(void **address)
{
	if (address && *address)
	{
		free(*address);
		*address = NULL;
		return (1);
	}

	return (0);
}


/**
 * fills_memory - fills memory with a constant byte
 * @ptr: the pointer to the memory area
 * @byte: the byte to fill *s with
 * @byteNum: the amount of bytes to be filled
 *
 *Return: (ptr) a pointer to the memory area
 */

char *fills_memory(char *ptr, char byte, unsigned int byteNum)
{
	unsigned int i;

	for (i = 0; i < byteNum; i++)
		ptr[i] = byte;

	return (ptr);
}

/**
 * free_string - frees a string of strings
 * @ptr_str: string of strings
 *
 * Return: void
 */

void free_string(char **ptr_str)
{
	char **address = ptr_str;

	if (!ptr_str)
		return;

	while (*ptr_str)
		free(*ptr_str++);

	free(address);
}

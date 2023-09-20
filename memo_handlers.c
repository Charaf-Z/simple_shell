#include "main.h"

/**
 * _memset - Fills the first n bytes of memory with a constant byte.
 * @string: Pointer to the memory area to be filled.
 * @byte: The constant byte to fill the memory with.
 * @length: The number of bytes to fill.
 * Return: A pointer to the memory area @string.
 */
char *_memset(char *string, char byte, unsigned int length)
{
	unsigned int i;

	for (i = 0; i < length; i++)
		string[i] = byte;
	return (string);
}

/**
 * ffree - Frees a double pointer array of strings and the array itself.
 * @pp: Pointer to the array of pointers to strings.
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp), pp++;
	free(a);
}

/**
 * Null_free - Frees a pointer and sets it to NULL.
 * @ptr: Pointer to the pointer to be freed.
 * Return: 1 (Success)
 */
int Null_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

/**
 * _realloc - function that reallocates a memory block using malloc and free
 * @ptr: pointer to the memory previously allocated
 * @old_size: size of allocated space for @ptr
 * @new_size: size of the new memory block
 * Return: pointer to the newly allocated memory block
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *p;
	unsigned int i;

	if (!ptr)
		return (malloc(new_size));
	if (new_size == old_size)
		return (ptr);
	if (new_size == 0 && ptr)
	{
		free(ptr);
		return (NULL);
	}
	p = malloc(new_size);
	if (!p)
		return (NULL);
	for (i = 0; i < old_size && i < new_size; i++)
		*((char *)p + i) = *((char *)ptr + i);
	free(ptr);
	return (p);
}

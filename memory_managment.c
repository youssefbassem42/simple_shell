#include "shell_lib.h"

/**
 * *_realloc - reallocat memory in the heap using malloc and free
 * @pointer: pointer to the memory allocated using malloc
 * @old_size: size of the old block of memory
 * @new_size: the size of the new memory block to reallocate
 *
 * Return: pointer that pointing to the new block of memory
 */
void *_realloc(void *pointer, unsigned int old_size, unsigned int new_size)
{
	char *pointer_1;

	if (!pointer)
		return (malloc(new_size));
	if (!new_size)
	{
		free(pointer);
		return (NULL);
	}
	if (new_size == old_size)
		return (pointer);
	pointer_1 = malloc(new_size);
	if (!pointer_1)
		return (NULL);
	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		pointer_1[old_size] = ((char *)pointer)[old_size];
	free(pointer);
	return (pointer_1);
}
/**
 * _memory_inisializer - function used for filling a byte of memory with values
 * @ptr: pointer to memory block to fill
 * @value: the value to fill
 * @size: the size of memory block in bytes
 *
 * Return: pointer to the block of memory that filled with data
*/
char *_memory_inisializer(char *ptr, char value, unsigned int  size)
{
	unsigned int i;

	for (i = 0; i < size ; i++)
		ptr[i] = value;

	return (ptr);
}
/**
 * frees - free the allocated pointer and set it to NULL
 * @pointer: the choosen pointer to be free
 *
 * Return: 1 if Success , 0 if it fails
*/
int frees(void **pointer)
{
	if (pointer && *pointer)
	{
		free(*pointer);
		*pointer = NULL;
		return (1);
	}
	return (0);
}
/**
 * free_str - delete and free the string of strings
 * @string: the string of strings to be freed
*/
void free_str(char **string)
{
	char **locator = string;

	if (!string)
		return;
	while (*string)
		free(*string++);
	free(locator);
}

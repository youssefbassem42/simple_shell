#include "shell_lib.h"

/**
 * err_put - print string
 * @e: string
*/

void err_put(char *e)
{
	int index = 0;

	if (!e)
		return;
	while (e[index] != '\0')
	{
		err_putchar(e[index]);
		index++;
	}
}

/**
 * err_putchar - write character to standered error
 * @s: character to print
 * Return: 1 if success , -1 on error cases
*/

int err_putchar(char s)
{
	static int index;
	static char buffer[WRITE_BUFFER_SIZE];

	if (s == BUFFER_FLUSH || index >= WRITE_BUFFER_SIZE)
	{
		write(2, buffer, index);
		index = 0;
	}
	if (s != BUFFER_FLUSH)
		buffer[index++] = s;
	return (1);
}

/**
 * _putfiled - write character in file discriptor
 * @s: character
 * @file: file descriptor to write in
 *
 * Return: 1 if success , -1 on error
*/

int _putfiled(char s, int file)
{
	static int index;
	static char buffer[WRITE_BUFFER_SIZE];

	if (s == BUFFER_FLUSH || index >= WRITE_BUFFER_SIZE)
	{
		write(file, buffer, index);
		index = 0;
	}
	if (s != BUFFER_FLUSH)
		buffer[index++] = s;
	return (1);
}

/**
 * putsfiled - print inputed string
 * @string: string
 * @filed: file discriptor
 *
 *Return: number of characters put in
*/
int putsfiled(char *string, int filed)
{
	int index = 0;

	if (!string)
		return (0);
	while (*string)
	{
		index += _putfiled(*string++, filed);
	}
	return (index);
}

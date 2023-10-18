#include "shell_lib.h"

/**
 * _putchar - write character ch to stdout
 * @ch: The character to print
 *
 * Return: On success (1).
 * On error: (-1) is returned, and errno sets appropriately.
 */

int _putchar(char ch)
{
	static int i;
	static char buf[WRITE_BUFFER_SIZE];

	if (ch == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (ch != BUFFER_FLUSH)
		buf[i++] = ch;
	return (1);
}

/**
 * _puts - print string
 * @string: pointer to string
 */

void _puts(char *string)
{
	int i = 0;

	if (!string)
		return;
	while (string[i] != '\0')
	{
		_putchar(string[i]);
		i++;
	}
}
/**
 * _strlen - calculate the number of charecters in string
 * @string: string to be calculated
 *
 * Return: length of string if true , 0 if the length is zero
*/
int _strlen(char *string)
{
	int i = 0;

	if (!string)
		return (0);

	while (*string++)
		i++;
	return (i);
}
/**
 * _strcmp - perform a  comparison of two strings.
 * @string_1: first string
 * @string_2: second string
 *
 * Return: positive if s1 > s2, negative if string_1 < string_2
 * , zero if string_1 == string_2
 */
int _strcmp(char *string_1, char *string_2)
{
	while (*string_1 && *string_2)
	{
		if (*string_1 != *string_2)
			return (*string_1 - *string_2);
		string_1++;
		string_2++;
	}
	if (*string_1 == *string_2)
		return (0);
	else
		return (*string_1 < *string_2 ? -1 : 1);
}

/**
 * str_concationation - get ends of input and add together for size
 * @string_1: input one to concat
 * @string_2: input two to concat
 * Return: concat of string_1 and string_2
 */
char *str_concationation(char *string_1, char *string_2)
{
	char *ret = string_1;

	while (*string_1)
		string_1++;
	while (*string_2)
		*string_1++ = *string_2++;
	*string_1 = *string_2;
	return (ret);
}

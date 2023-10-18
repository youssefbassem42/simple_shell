#include "shell_lib.h"

/**
 * _strcpy - copies a string to another
 * @first_1: the first string
 * @source_1: the source string
 *
 * Return: pointer to the final destination
 */
char *_strcpy(char *first_1, char *source_1)
{
	int i = 0;

	if (first_1 == source_1 || source_1 == 0)
		return (first_1);
	while (source_1[i])
	{
		first_1[i] = source_1[i];
		i++;
	}
	first_1[i] = 0;
	return (first_1);
}
/**
 * _strdup - duplicates a string
 * @string: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *string)
{
	int length = 0;
	char *ret;

	if (string == NULL)
		return (NULL);
	while (*string++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--string;
	return (ret);
}

/**
 * start_with - check if con_str starts with search_for
 * @con_str: sub string to find
 * @search_for: string that looking for
 *
 * Return: adress of search_for if success , NULL if fails
*/

char *start_with(const char *con_str, const char *search_for)
{
	while (*con_str)
		if (*con_str++ != *search_for++)
			return (NULL);

	return ((char *)search_for);
}

#include "shell_lib.h"

/**
 **_strncpy - string copy function
 *@st: string to copy from it
 *@sorc: source string
 *@num: number of character to copy
 *Return: the final string concatination
*/
char *_strncpy(char *st, char *sorc, int num)
{
	int i, j;
	char *s = st;

	i = 0;
	while (sorc[i] != '\0' && i < num - 1)
	{
		st[i] = sorc[i];
		i++;
	}
	if (i < num)
	{
		j = i;
		while (j < num)
		{
			st[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenates two strings
 *@s1: 1st string
 *@s2: 2nd string
 *@num: amount of bytes to use
 *Return: string concatinated
 */
char *_strncat(char *s1, char *s2, int num)
{
	int i, j;
	char *s = s1;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
		i++;
	while (s2[j] != '\0' && j < num)
	{
		s1[i] = s2[j];
		i++;
		j++;
	}
	if (j < num)
		s1[i] = '\0';
	return (s);
}

/**
 **str_char - search for character index in string
 *@s:string to be parsed
 *@c:character searching for it
 *Return: (s) a pointer to the memory area s
 */
char *str_char(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

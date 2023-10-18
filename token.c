#include "shell_lib.h"

/**
 * **strtoken - split string into words
 * @string: the input string
 * @delims: the delimeter string
 *
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtoken(const char *string, const char *delims)
{
	int i = 0, j, k, m, number_words = 0, words_index = 0;
	char **words;

	if (string == NULL || *string == '\0')
		return (NULL);
	if (delims == NULL)
		delims = " ";
	while (string[i] != '\0')
	{
		if (!is_delim(string[i], delims))
			if (is_delim(string[i + 1], delims) || *(string + i + 1) == '\0')
				number_words++;
		i++;
	}
	words = malloc(sizeof(char *) * (number_words + 1));
	if (words == NULL)
		return (NULL);
	for (i = 0, j = 0; j < number_words; j++)
	{
		while (is_delim(string[i], delims))
			i++;
		k = 0;
		while (!is_delim(string[i + k], delims) && string[i + k] != '\0')
			k++;
		words[words_index] = malloc((k + 1) * sizeof(char));
		if (words[words_index] == NULL)
		{
			for (m = 0; m < words_index; m++)
				free(words[m]);
			free(words);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			words[words_index][m] = string[i++];

		words[words_index][m] = '\0';
		words_index++;
	}
	words[words_index] = NULL;
	return (words);
}

/**
 * is_delim - check if the character is delimiter or not
 * @c: char to check
 * @delim: delimiters , NULL == whitespace
 * Return: 1 if true , 0 if false
*/
int is_delim(char c, const char *delim)
{
	if (!*delim)
		delim = " ";
	while (*delim)
	{
		if (c == *delim)
			return (1);
		delim++;
	}
	return (0);
}

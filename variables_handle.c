#include "shell_lib.h"

/**
 * string_changer - change string from the old to new one
 * @o: old string to change with
 * @n: new string
 *
 * Return: 1 if success , 0 if fails
*/

int string_changer(char **o, char *n)
{
	free(*o);
	*o = n;
	return (1);
}

/**
 * is_chain - check if the buffer character is chain command or not
 * @info: Parameters to Evaluate with
 * @buffer: the Buffer of the command
 * @ptr: the address of the current position
 * Return: 1 if chaining command
*/

int is_chain(info *info, char *buffer, size_t *ptr)
{
	size_t i = *ptr;

	if (buffer[i] == '|' && buffer[i + 1] == '|')
	{
		buffer[i] = 0;
		i++;
		info->cmd_buff_type = CMD_OR;
	}
	else if (buffer[i] == '&' && buffer[i + 1] == '&')
	{
		buffer[i] = 0;
		i++;
		info->cmd_buff_type = CMD_AND;
	}
	else if (buffer[i] == ';')
	{
		buffer[i] = 0;
		info->cmd_buff_type = CMD_CHAIN;
	}
	else
		return (0);
	*ptr = i;
	return (1);
}

/**
 * alias_changer - change the aliases from the tokenizer
 * @info: parameters to evaluate
 *
 * Return: 1 if changed , 0 if fails
*/
int alias_changer(info *info)
{
	int counter;
	list_t *new_node;
	char *pointer;

	for (counter = 0; counter < 10; counter++)
	{
		new_node = node_searcher(info->alias, info->argv[0], '=');
		if (!new_node)
			return (0);
		free(info->argv[0]);
		pointer = str_char(new_node->string, '=');
		if (!pointer)
			return (0);
		pointer = _strdup(pointer + 1);
		if (!pointer)
			return (0);
		info->argv[0] = pointer;
	}
	return (1);
}

/**
 * chain_checker - check if break chaining or containue
 * @info: parameters to evalute
 * @buffer: the buffer of the character
 * @st: position to start from
 * @pos: the address of the position of the buffer
 * @length: length of the buffer
*/
void chain_checker(info *info, char *buffer, size_t *pos
	, size_t st, size_t length)
{
	size_t j = *pos;

	if (info->cmd_buff_type == CMD_AND)
	{
		if (info->status)
		{
			buffer[st] = 0;
			j = length;
		}

	}
	if (info->cmd_buff_type == CMD_OR)
	{
		if (!info->status)
		{
			buffer[st] = 0;
			j = length;
		}

	}
	*pos = j;
}

/**
 * var_change - change and replacing the tokenizer from the string
 * @info: parameters to evaluate
 *
 * Return: 1 if success , 0 if fails
*/

int var_change(info *info)
{
	int counter = 0;
	list_t *node;

	for (counter = 0; info->argv[counter]; counter++)
	{
		if (info->argv[counter][0] != '$' || !info->argv[counter][1])
			continue;
		if (!_strcmp(info->argv[counter], "$?"))
		{
			string_changer(&(info->argv[counter]),
				 _strdup(number_converter(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[counter], "$$"))
		{
			string_changer(&(info->argv[counter]),
				 _strdup(number_converter(getpid(), 10, 0)));
			continue;
		}
		node = node_searcher(info->env, &info->argv[counter][1], '=');
		if (node)
		{
			string_changer(&(info->argv[counter]),
				_strdup(str_char(node->string, '=') + 1));
			continue;
		}
		string_changer(&info->argv[counter], _strdup(""));
	}
	return (0);
}

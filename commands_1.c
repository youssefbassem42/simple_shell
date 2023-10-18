#include "shell_lib.h"

/**
 * _alias - alias builtin
 * @info: parameters to evaluate
 *
 *Return: 0 if Success , 1 if fails
*/

int _alias(info *info)
{
	int counter = 0;
	char *ptr = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			alias_printer(node);
			node = node->next;
		}
		return (0);
	}
	for (counter = 1; info->argv[counter]; counter++)
	{
		ptr = str_char(info->argv[counter], '=');
		if (ptr)
			alias_def(info, info->argv[counter]);
		else
			alias_printer(node_searcher(info->alias, info->argv[counter], '='));
	}
	return (0);
}

/**
 * clear_alias - set string alias
 * @info: parameters to evaluate
 * @string: string alias
 *
 *Return: 0 if success, 1 if fails
*/
int clear_alias(info *info, char *string)
{
	char *ptr, c;
	int retrn;

	ptr = str_char(string, '=');
	if (!ptr)
		return (1);
	c = *ptr;
	*ptr = 0;
	retrn = delete_at(&(info->alias),
		get_index(info->alias, node_searcher(info->alias, string, -1)));
	*ptr = c;
	return (retrn);
}
/**
 * alias_def - define a alias to string
 * @info: parameters to evaluate
 * @string: string alias
 *
 * Return: 0 on success , 1 if fails
*/
int alias_def(info *info, char *string)
{
	char *ptr;

	ptr = str_char(string, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (clear_alias(info, string));
	clear_alias(info, string);
	return (add_end(&(info->alias), string, 0) == NULL);
}

/**
 * alias_printer - print alias string
 * @ptr: alias node
 *
 * Return: 0 if success, 1 if fails
*/
int alias_printer(list_t *ptr)
{
	char *p = NULL, *c = NULL;

	if (ptr)
	{
		p = str_char(ptr->string, '=');
		for (c = ptr->string; c <= p; c++)
			_putchar(*c);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
/**
 * history_saver - list the history of used commands
 * @info: parameters to evaluate
 * Return: 0 always
*/

int history_saver(info *info)
{
	list_printer(info->history);
	return (0);
}

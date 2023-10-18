#include "shell_lib.h"

/**
 * _env - print the working environment
 * @info: parameters to evaluate
 *
 * Return: 0 Always
*/

int _env(info *info)
{
	print_string(info->env);
	return (0);
}

/**
 * env_init - initialize environment variable
 * @info: parameters to evaluate
 *
 * Return: 0
*/
int env_init(info *info)
{
	if (info->argc != 3)
	{
		err_put("incorrect number of arguements\n");
		return (1);
	}
	if (env_set(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}
/**
 * _getenv - environment variable handle
 * @info:parameters to evaluate
 * @n: the name of the variable
 *
 *Return: value of the variable
*/
char *_getenv(info *info, const char *n)
{
	list_t *node_s = info->env;
	char *ptr;

	while (node_s)
	{
		ptr = start_with(node_s->string, n);
		if (ptr && *ptr)
			return (ptr);
		node_s = node_s->next;
	}
	return (NULL);
}
/**
 * un_env - clear environment var
 * @info:parameters to evaluate
 *
 * Return: 0
*/
int un_env(info *info)
{
	int counter;

	if (info->argc == 1)
	{
		err_put("Too few argument.\n");
		return (1);
	}
	for (counter = 1; counter <= info->argc; counter++)
		clear_env(info, info->argv[counter]);
	return (0);
}

/**
 * env_list - add a variable to the environment list
 * @info: parameters to evaluate
 *
 * Return: 0
*/
int env_list(info *info)
{
	list_t *node = NULL;
	size_t counter;

	for (counter = 0; environ[counter]; counter++)
		add_end(&node, environ[counter], 0);
	info->env = node;
	return (0);
}

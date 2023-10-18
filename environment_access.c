#include "shell_lib.h"

/**
 * env_set - new environment var initializtion
 * @info: parameters to evaluate
 * @v: string variable
 * @en_v: string in env
 * Return: 0
*/
int env_set(info *info, char *v, char *en_v)
{
		char *buffer = NULL;
		list_t *n;
		char *pointer;

		if (!v || !en_v)
			return (0);
		buffer = malloc(_strlen(v) + _strlen(en_v) + 2);
		if (!buffer)
			return (1);
		_strcpy(buffer, v);
		str_concationation(buffer, "=");
		str_concationation(buffer, en_v);
		n = info->env;
		while (n)
		{
			pointer = start_with(n->string, v);
			if (pointer && *pointer == '=')
			{
				free(n->string);
				n->string = buffer;
				info->env_changed = 1;
				return (0);
			}
			n = n->next;
		}
		add_end(&(info->env), buffer, 0);
		free(buffer);
		info->env_changed = 1;
		return (0);
}

/**
 * env_getter - copies the string of environment
 * @info: parameters to evaluate
 *
 * Return: 0
*/
char **env_getter(info *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = strings_of_list(info->env);
		info->env_changed = 0;
	}
	return (info->environ);
}

/**
 * clear_env - delete a variable from the environment
 *@info: parameters to evaluate
 *@v: variable name
 * Return: 1 if deleted, 0 if fails
*/

int clear_env(info *info, char *v)
{
	list_t *n = info->env;
	size_t counter = 0;
	char *ptr;

	if (!n || !v)
		return (0);
	while (n)
	{
		ptr = start_with(n->string, v);
		if (ptr && *ptr == '=')
		{
			info->env_changed = delete_at(&(info->env), counter);
			counter = 0;
			n = info->env;
			continue;
		}
		n = n->next;
		counter++;
	}
	return (info->env_changed);
}

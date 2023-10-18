#include "shell_lib.h"

/**
 * clear_info - delete allocated data in info structue
 * @info: address of the structure
 * @v: free all data if the value is true
*/
void clear_info(info *info, int v)
{
	free_str(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (v)
	{
		if (!info->cmd_buffer)
			free(info->argument);
		if (info->env)
			list_is_free(&(info->env));
		if (info->history)
			list_is_free(&(info->history));
		if (info->alias)
			list_is_free(&(info->alias));
		free_str(info->environ);
			info->environ = NULL;
		frees((void **)info->cmd_buffer);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUFFER_FLUSH);
	}

}

/**
 * delete_info - initializtion of the info structure
 * @info: the structure address
*/

void delete_info(info *info)
{
	info->argument = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * init_info - inisialize of the info parameters
 * @info: parameters to evaluate with
 * @string: the string to inisialize
*/

void init_info(info *info, char **string)
{
	int counter = 0;

	info->filename = string[0];
	if (info->argument)
	{
		info->argv = strtoken(info->argument, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->argument);
				info->argv[1] = NULL;
			}
		}
		for (counter = 0; info->argv && info->argv[counter]; counter++)
			;
		info->argc = counter;
		alias_changer(info);
		var_change(info);
	}
}

#include "shell_lib.h"

/**
 * prompt - shell loop
 * @info: parameters to evalaute
 * @argument: vector argument
 *
 * Return: 0 if success , 1 if fails , error code if fails too
*/

int prompt(info *info, char **argument)
{
	ssize_t reader = 0;
	int built = 0;

	while (reader != -1 && built != -2)
	{
		delete_info(info);
		if (is_interactive(info))
			_puts(":) ");
		err_putchar(BUFFER_FLUSH);
		reader = input_getter(info);
		if (reader != -1)
		{
			init_info(info, argument);
			built = builtin_finder(info);
			if (built == -1)
				command_finder(info);
		}
		else if (is_interactive(info))
			_putchar('\n');
		clear_info(info, 0);
	}
	out_history(info);
	clear_info(info, 1);
	if (!is_interactive(info) && info->status)
	{
		exit(info->status);
	}

	if (built == -2)
	{
		if (info->erro_number == -1)
			exit(info->status);
		exit(info->erro_number);
	}
	return (built);
}

/**
 * command_fork - fork an executed thread to run command
 * @info: parameters to evaluate
*/
void command_fork(info *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, env_getter(info)) == -1)
		{
			clear_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				error_poper(info, "Permission denied\n");
		}
	}
}


/**
 * builtin_finder - find the builtin commands
 * @info: parameters to evaluate
 *
 * Return: 0 if the builtin found and executed, -1 if the builtin not found,
 * 2 if the builtin is exit or signal to exit,
 *	1 if builtin found but there is an error
*/

int builtin_finder(info *info)
{
	int counter, built = -1;
	built_in table[] = {
		{"exit", exit_ex},
		{"env", _env},
		{"history", history_saver},
		{"setenv", env_init},
		{"unsetenv", un_env},
		{"cd", cder},
		{"alias", _alias},
		{NULL, NULL}
	};

	if (info->argv[0] == NULL)
		return (-1);
	for (counter = 0; table[counter].type; counter++)
		if (_strcmp(info->argv[0], table[counter].type) == 0)
		{
			info->line_counter++;
			built = table[counter].function(info);
			break;
		}
	return (built);
}


/**
 * command_finder - find command path
 * @info: parameters to evaluate
*/
void command_finder(info *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_counter++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->argument[i]; i++)
		if (!is_delim(info->argument[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = path_finder(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		command_fork(info);
	}
	else
	{
		if ((is_interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_command(info, info->argv[0]))
		{
			command_fork(info);
		}
		else if (*(info->argument) != '\n')
		{
			info->status = 127;
			error_poper(info, "not found\n");
		}
	}
}

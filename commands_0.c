#include "shell_lib.h"

/**
 * exit_ex - exit command from the shell
 * @info: parameters to evaluate
 *
 * Return: exit status , 0 if argument vector isn't exit command
*/

int exit_ex(info *info)
{
	int checker;

	if (info->argv[1])
	{
		checker = atoi_error(info->argv[1]);
		if (checker == -1)
		{
			info->status = 2;
			error_poper(info, "Illegal number: ");
			err_put(info->argv[1]);
			err_putchar('\n');
			return (1);
		}
		info->erro_number = atoi_error(info->argv[1]);
		return (-2);
	}
	info->erro_number = -1;
	return (-2);
}
/**
 * cder - change the current working directory
 * @info: parameters to evaluate
 *
 * Return: 0 ALways
*/
int cder(info *info)
{
	char *current, *directory, buffer[1024];
	int changed_dir;

	current = getcwd(buffer, 1024);
	if (!current)
		_puts("not such a file or directory");
	if (!info->argv[1])
	{
		directory = _getenv(info, "HOME=");
		if (!directory)
			changed_dir =
				chdir((directory = _getenv(info, "PWD=")) ? directory : "/");
		else
			changed_dir = chdir(directory);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(current);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		changed_dir =
		chdir((directory = _getenv(info, "OLDPWD=")) ? directory : "/");
	}
	else
		changed_dir = chdir(info->argv[1]);
	if (changed_dir == -1)
	{
		error_poper(info, "can't cd to ");
		err_put(info->argv[1]), err_putchar('\n');
	}
	else
	{
		env_set(info, "OLDPWD", _getenv(info, "PWD="));
		env_set(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

#include "shell_lib.h"

/**
 * path_finder - searching for pathes in the string
 * @info: Parametars to Evaluate with
 * @path_string: String Path
 * @command: Command searching for
 *
 * Return: full path if Success , NULL if fails
*/

char *path_finder(info *info, char *path_string, char *command)
{
	int index = 0, current_positin = 0;
	char *path;

	if (!path_string)
		return (NULL);
	if ((_strlen(command) > 2) && start_with(command, "./"))
	{
		if (is_command(info, command))
			return (command);
	}
	while (1)
	{
		if (!path_string[index] || path_string[index] == ':')
		{
			path = string_dupicator(path_string, current_positin, index);
			if (!*path)
				str_concationation(path, command);
			else
			{
				str_concationation(path, "/");
				str_concationation(path, command);
			}
			if (is_command(info, path))
				return (path);
			if (!path_string[index])
				break;
			current_positin = index;
		}
		index++;
	}
	return (NULL);
}

/**
 * is_command - check if the command is executable or not by using stat struct
 * @info: Parametars to Evaluate with
 * @path: path of the file
 * Return: 0 Always
*/

int is_command(info *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);
	if (st.st_mode & S_IFREG)
	{
		return (1);
	}

	return (0);
}

/**
 * string_dupicator - duplicate string
 * @path_str: the path of the string
 * @s: the start value
 * @sp: the stop value
 *
 * Return: Pointer to New Buffer
*/

char *string_dupicator(char *path_str, int s, int sp)
{
	static char buffer[1024];
	int counter = 0, index = 0;

	for (index = 0, counter = s; counter < sp; counter++)
		if (path_str[counter] != ':')
			buffer[index++] = path_str[counter];
	buffer[index] = 0;
	return (buffer);
}

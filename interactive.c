#include "shell_lib.h"

/**
 * is_interactive - check if the Shell is in interactive Mode
 * @info: Parameters to Evaluate with it
 * Return: true if in interactive , 0 if otherwise
*/
int is_interactive(info *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}


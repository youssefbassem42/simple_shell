#include "shell_lib.h"
/**
 * main - entry point
 * @ac: argument counter
 * @av: array of strings that hold arguments
 *
 * Return: 0 on success, 1 on fail
 */
int main(int ac, char **av)
{
	info info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				err_put(av[0]);
				err_put(": 0: Can't open ");
				err_put(av[1]);
				err_putchar('\n');
				err_putchar(BUFFER_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	env_list(info);
	in_history(info);
	prompt(info, av);
	return (EXIT_SUCCESS);
}

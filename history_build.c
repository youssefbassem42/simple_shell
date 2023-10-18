#include "shell_lib.h"

/**
 * get_history - return the history file
 * @info: parameters to evaluate
 *
 * Return: string contain the history file
*/
char *get_history(info *info)
{
	char *buffer, *directory;

	directory = _getenv(info, "HOME=");
	if (!directory)
		return (NULL);
	buffer =
	malloc(sizeof(char) * (_strlen(directory) + _strlen(HISTORY_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, directory);
	str_concationation(buffer, "/");
	str_concationation(buffer, HISTORY_FILE);
	return (buffer);
}

/**
 * in_history - read history file
 * @info: parameters to evaluate
 *
 * Return: history count, 0 if fails
*/
int in_history(info *info)
{
	int i, last = 0, linecounter = 0;
	ssize_t filed, rdlen, fsize = 0;
	struct stat st;
	char *buffer = NULL, *filename = get_history(info);

	if (!filename)
		return (0);
	filed = open(filename, O_RDONLY);
	free(filename);
	if (filed == -1)
		return (0);
	if (!fstat(filed, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (fsize + 1));
	if (!buffer)
		return (0);
	rdlen = read(filed, buffer, fsize);
	buffer[fsize] = 0;
	if (rdlen <= 0)
		return (free(buffer), 0);
	close(filed);
	for (i = 0; i < fsize; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			history_build(info, buffer + last, linecounter++);
			last = i + 1;
		}
	if (last != i)
		history_build(info, buffer + last, linecounter++);
	free(buffer);
	info->histcount = linecounter;
	while (info->histcount-- >= HISTORY_MAX)
		delete_at(&(info->history), 0);
	reinit_history(info);
	return (info->histcount);
}

/**
 * history_build - history build linkedlist
 * @info: parameters to evaluate
 * @buffer: buffer
 * @line: history counter
 *
 * Return: 0 Always
*/
int history_build(info *info, char *buffer, int line)
{
	list_t *n = NULL;

	if (info->history)
		n = info->history;
	add_end(&n, buffer, line);
	if (!info->history)
		info->history = n;
	return (0);

}

/**
 * reinit_history - re arrange the counter of the history after edit
 * @info: parameters to evaluate
 *Return: new number count
*/

int reinit_history(info *info)
{
	list_t *n = info->history;
	int counter = 0;

	while (n)
	{
		n->number = counter++;
		n = n->next;
	}
	return (info->histcount = counter);
}

/**
 * out_history - create or append to exist file
 * @info: parameters to evaluate
 *
 * Return: 1 if success, -1 if fails
*/

int out_history(info *info)
{
	ssize_t filed;
	char *filename = get_history(info);
	list_t *n = NULL;

	if (!filename)
		return (-1);
	filed = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (filed == -1)
		return (-1);
	for (n = info->history; n; n = n->next)
	{
		putsfiled(n->string, filed);
		_putfiled('\n', filed);
	}
	_putfiled(BUFFER_FLUSH, filed);
	close(filed);
	return (1);
}

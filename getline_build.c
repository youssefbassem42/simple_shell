#include "shell_lib.h"
/**
 * fix_sigint - fix the sigint Ctrl+C
 * @sigint_number: Signal number
*/

void fix_sigint(__attribute__((unused))int sigint_number)
{
	_puts("\n");
	_puts(":) ");
	_putchar(BUFFER_FLUSH);
}

/**
 * input_buffer - buffer chain commands
 * @info: Parametars to evaluate with
 * @length: the address of the length variable
 * @buffer: the address of the buffer
 *
 * Return: The Readed Bytes
*/
ssize_t input_buffer(info *info, size_t *length, char **buffer)
{
ssize_t reader = 0;
size_t bufferLen = 0;

if (!*length)
{
	free(*buffer);
	*buffer = NULL;
	signal(SIGINT, fix_sigint);
		reader = _getline(info, &bufferLen, buffer);
	if (reader > 0)
	{
		if ((*buffer)[reader - 1] == '\n')
		{
			(*buffer)[reader - 1] = '\0';
			reader--;
		}
		info->linecount_flag = 1;
		delete_comment(*buffer);
		history_build(info, *buffer, info->histcount++);
		{
			*length = reader;
			info->cmd_buffer = buffer;
		}
	}
}
return (reader);
}

/**
 * buffer_reader - read the buffer
 * @size: the size of the buffer
 * @info: Parametars to evaluate with
 * @buffer: the Buffer to read
 * Return: readed buffer
*/

ssize_t buffer_reader(size_t *size, info *info, char *buffer)
{
	ssize_t readed = 0;

	if (*size)
		return (0);
	readed = read(info->readfd, buffer, READ_BUFFER_SIZE);
	if (readed >= 0)
	{
		*size = readed;
	}
	return (readed);
}

/**
 * _getline - get the line from the input
 * @info: Parameters to be Evaluated
 * @size: size of the allocate bytes
 * @pointer: address of the buffer
 *
 * Return:the total readed bytes
*/

int _getline(info *info, size_t *size, char **pointer)
	{
	static char buffer[READ_BUFFER_SIZE];
	static size_t currentIndex, bufferLength;
	size_t k;
	ssize_t bytesRead = 0, totalBytesRead = 0;
	char *p = NULL, *newPtr = NULL, *c;

	p = *pointer;
	if (p && size)
	{
		totalBytesRead = *size;
	}
	if (currentIndex == bufferLength)
	{
		currentIndex = 0;
		bufferLength = 0;
	}
	bytesRead = buffer_reader(&bufferLength, info, buffer);
	if (bytesRead == -1 || (bytesRead == 0 && bufferLength == 0))
		return (-1);
	c = str_char(buffer + currentIndex, '\n');
	k = c ? 1 + (unsigned int) (c - buffer) : bufferLength;
	newPtr = _realloc(p, totalBytesRead,
	totalBytesRead ? totalBytesRead + k : k + 1);
	if (!newPtr)
		return (p ? free(p), -1 : -1);
	if (totalBytesRead)
		_strncat(newPtr, buffer + currentIndex, k - currentIndex);
	else
		_strncpy(newPtr, buffer + currentIndex, k - currentIndex + 1);
	totalBytesRead += k - currentIndex;
	currentIndex = k;
	p = newPtr;
	if (size)
		*size = totalBytesRead;
	*pointer = p;
	return (totalBytesRead);
	}

/**
 * input_getter - get the input line
 * @info: Parameters to Evaluate with it
 *
 * Return: the input length of the bytes that Readed
*/

ssize_t input_getter(info *info)
{
	static char *command_buffer;
	static size_t command_pos, buffer_length, length_1;
	ssize_t input_length = 0;
	char **current_command = &(info->argument), *current_position;

	_putchar(BUFFER_FLUSH);
	input_length = input_buffer(info, &length_1, &command_buffer);

	if (input_length == -1)
		return (-1);

if (length_1)
{
	buffer_length = command_pos;
	current_position = command_buffer + command_pos;

	chain_checker(info, command_buffer, &buffer_length, command_pos, length_1);

		while (buffer_length < length_1)
		{
			if (is_chain(info, command_buffer, &buffer_length))
			break;
			buffer_length++;
		}
	command_pos = buffer_length + 1;

		if (command_pos >= length_1)
		{
			command_pos = 0;
			length_1 = 0;
			info->cmd_buff_type = CMD_NORMAL;
		}

		*current_command = current_position;
		return (_strlen(current_position));
}

	*current_command = command_buffer;
	return (input_length);
}

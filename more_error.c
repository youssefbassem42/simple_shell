#include "shell_lib.h"

/**
 * atoi_error - convert string to number
 * @string: string to convert
 * Return: 0 if string dosn't contain numbers,
 *      converted numbers if there, -1 if error
*/
int atoi_error(char *string)
{
	int index = 0;
	unsigned long int r = 0;

	if (*string == '+')
	{
		string++;
	}

	for (index = 0; string[index] != '\0'; index++)
	{
		if (string[index] >= '0' && string[index] <= '9')
		{
			r *= 10;
			r += (string[index] - '0');
			if (r > INT_MAX)
				return (-1);

		}
		else
			return (-1);
	}
	return (r);
}

/**
 * error_poper - print error massage
 * @info: parameters to evaluate
 * @err: error type string
*/
void error_poper(info *info, char *err)
{
	err_put(info->filename);
	err_put(": ");
	decimal_printer(info->line_counter, STDERR_FILENO);
	err_put(": ");
	err_put(info->argv[0]);
	err_put(": ");
	err_put(err);
}

/**
 * decimal_printer - print base 10 number
 * @i: input
 * @filed: file discriptor
 *
 * Return: number of characters
*/
int decimal_printer(int i, int filed)
{
	int (*putchar)(char) = _putchar;
	int index, c = 0;
	unsigned int abs, cur;

	if (filed == STDERR_FILENO)
		putchar = err_putchar;
	if (i < 0)
	{
		abs = -i;
		putchar('-');
		c++;
	}
	else
		abs = i;
	cur = abs;
	for (index = 1000000000; index > 1; index /= 10)
	{
		if (abs / index)
		{
			putchar('0' + cur / index);
			c++;
		}
		c %= index;
	}
	putchar('0' + cur);
	c++;
	return (c);
}

/**
 * delete_comment - remove hash and repalce it with \0
 * @buffer: string to modify
*/
void delete_comment(char *buffer)
{
	int index;

	for (index = 0; buffer[index] != '\0'; index++)

		if (buffer[index] == '#' && (!index || buffer[index - 1] == ' '))
		{
			buffer[index] = '\0';
			break;
		}


}
/**
 * number_converter - itoa function
 *@number: number
 * @base: base
 * @flag: flag
 * Return: string
*/
char *number_converter(long int number, int base, int flag)
{
	static char *ar;
	static char buffer[50];
	char sign_v = 0;
	char *pointer;
	unsigned long v = number;

	if (!(flag & CONVERT_UNSIGNED) && number < 0)
	{
		v = -number;
		sign_v = '-';
	}
	ar = flag & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pointer = &buffer[49];
	*pointer = '\0';

	do {
		*--pointer = ar[v % base];
		v /= base;
	} while (v != 0);
	if (sign_v)
		*--pointer = sign_v;
	return (pointer);
}

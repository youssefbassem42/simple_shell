#include "shell_lib.h"

/**
 * list_length - calculate the length of the given linked list
 * @list: linked list to be evaluated
 *
 * Return: the number of elements in the linked list
*/

size_t list_length(const list_t *list)
{
	size_t i = 0;

	while (list)
	{
		list =  list->next;
		i++;
	}
	return (i);
}

/**
 * list_printer - print the linked list elements
 * @head: linked list first node pointer
 *
 * Return: length of the linked list
*/

size_t list_printer(const list_t *head)
{
	size_t counter = 0;

	while (head)
	{
		_puts(number_converter(head->number, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->string ? head->string : "(nil)");
		_puts("\n");
		head = head->next;
		counter++;
	}
	return (counter);
}

/**
 * node_searcher - search for the node with prefix
 * @second: the second char after the prefix
 * @pre: the prefix of the search
 * @point: pointer to the first node in linked list
 * Return: the node if success , NULL if fails
*/

list_t *node_searcher(list_t *point, char *pre, char second)
{
	char *saver = NULL;

	while (point)
	{
		saver = start_with(point->string, pre);
		if (saver && ((*saver == second) || (second == -1)))
			return (point);
		point = point->next;
	}
	return (NULL);
}
/**
 * strings_of_list - get the string data from the linked list
 * @head: first node of the linked list
 *
 * Return: array of strings contained in the linked list
*/
char **strings_of_list(list_t *head)
{
	list_t *temp = head;
	size_t counter_0 = list_length(head), counter_1;
	char **strings_array;
	char *string_saver;

	if (!head || !counter_0)
		return (NULL);
	strings_array = malloc(sizeof(char *) * (counter_0 + 1));
	if (!strings_array)
		return (NULL);
	for (counter_0 = 0; temp ; temp = temp->next, counter_0++)
	{
		string_saver = malloc(_strlen(temp->string) + 1);
		if (!string_saver)
		{
			for (counter_1 = 0; counter_1 < counter_0; counter_1++)
				free(strings_array[counter_1]);
			free(strings_array);
			return (NULL);
		}

		string_saver = _strcpy(string_saver, temp->string);
		strings_array[counter_0] = string_saver;
	}
	strings_array[counter_0] = NULL;
	return (strings_array);
}
/**
 * get_index - get the node index in the linked list
 * @the_node: node to calculate the index for
 * @head_point: the head pointer in the linked list;
 *
 * Return: the index if success , -1 if it fails
*/

ssize_t get_index(list_t *head_point, list_t *the_node)
{
	size_t counter = 0;

	while (head_point)
	{
		if (head_point == the_node)
			return (counter);
		head_point = head_point->next;
		counter++;
	}
	return (-1);
}

#include "shell_lib.h"

/**
 * add_first - adding a new node at the begginning of the linked list
 * @head: the head pointer of the linked list
 * @string: the string to put into linked list node
 * @number: the number of the node in the history
 * Return: the node that added first of the list
*/

list_t *add_first(list_t **head, const char *string, int number)
{
	list_t *new_node;

	if (!head)
		return (NULL);
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memory_inisializer((void *)new_node, 0, sizeof(list_t));
	new_node->number = number;
	if (string)
	{
		new_node->string = _strdup(string);
		if (!new_node->string)
		{
			free(new_node);
			return (NULL);
		}
	}
	new_node->next = *head;
	*head = new_node;
	return (new_node);
}

/**
 * print_string - print the string part of the linked list
 * @head: pointer to the first element of the linked list
 *
 * Return: length of the linked list
*/
size_t print_string(const list_t *head)
{
	size_t counter = 0;

	while (head)
	{
		_puts(head->string ? head->string : "(nil)");
		_puts("\n");
		head = head->next;
		counter++;
	}
	return (counter);
}

/**
 * add_end - adding new node to the end of the linked list
 * @string: the given string to add to the node data
 * @number: number of index
 * @head: the first node pointer for the linked list
 * Return: the node that added to the end of the linked list
*/

list_t *add_end(list_t **head, const char *string, int number)
{
	list_t *new_node, *temp;

	if (!head)
		return (NULL);
	temp = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	_memory_inisializer((void *)new_node, 0, sizeof(list_t));
	new_node->number = number;
	if (string)
	{
		new_node->string = _strdup(string);
		if (!new_node->string)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (temp)
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;

	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * delete_at - delete node at spesific index
 * @head: pointer of the first node at linked list
 * @index: the index of the given node to delete at
 *
 * Return: 0 if fails , 1 if success
*/

int delete_at(list_t **head, unsigned int index)
{
	list_t *temp, *prev_node;
	unsigned int counter = 0;

	if (!*head || !head)
		return (0);
	if (!index)
	{
		temp = *head;
		*head = (*head)->next;
		free(temp->string);
		free(temp);
		return (1);
	}
	temp = *head;
	while (temp)
	{
		if (counter == index)
		{
			prev_node->next = temp->next;
			free(temp->string);
			free(temp);
			return (1);
		}
		counter++;
		prev_node = temp;
		temp = temp->next;
	}
	return (0);
}
/**
 * list_is_free - frees the elements from the given linked list
 * @head: the head pointer of the given linked list to free it
*/

void list_is_free(list_t **head)
{
	list_t *head_temp, *temp, *next;

	if (!head || !*head)
		return;
	head_temp = *head;
	temp = head_temp;
	while (temp)
	{
		next = temp->next;
		free(temp->string);
		free(temp);
		temp = next;
	}
	*head = NULL;
}

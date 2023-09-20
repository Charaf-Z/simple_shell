#include "main.h"

/**
 * add_node_end - adds a new node at the end of a linked list
 * @head: address of pointer to the head
 * @str: string to put in the new node
 * @num: node index
 * Return: address of the new element, or NULL if it failed
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node = malloc(sizeof(list_t));
	list_t *node = *head;

	if (!head || !new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = str_dup(str);
		if (!new_node->str)
			return (free(new_node), NULL);
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_list - Prints the elements of a linked list.
 * @h: Pointer to the head of the linked list.
 * Return: the number of elements in the list.
 */
size_t print_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		print_string(convert_number(h->num, 10, 0));
		print_string(": ");
		print_string(h->str ? h->str : "(nil)");
		print_string("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * print_list_string - prints a linked lists
 * @head: pointer to first node
 * Return: size of list
 */
size_t print_list_string(const list_t *head)
{
	size_t i = 0;

	while (head)
	{
		print_string(head->str ? head->str : "(nil)");
		print_char('\n');
		head = head->next;
		i++;
	}
	return (i);
}

/**
 * list_to_strings - Converts a linked list of strings
 *			to an array of strings.
 * @head: Pointer to the head of the linked list.
 * Return: the array of strings if successful, or NULL.
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_length(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(str_length(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}
		str = str_cpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

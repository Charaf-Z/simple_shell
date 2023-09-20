#include "main.h"

/**
 * list_length - returns the number of elements in a linked list
 * @h: pointer to first node
 * Return: size of list
 */
size_t list_length(const list_t *h)
{
	size_t i = 0;

	while (h)
		i++, h = h->next;
	return (i);
}

/**
 * delete_node_at_index - deletes a node at the given index
 * @head: pointer to the head
 * @index: index of the node to delete
 * Return: 1 (Success), or 0 (Fail)
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int idx = 0;

	if (!head || !*head)
		return (0);
	node = *head;
	if (!index)
	{
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	while (node)
	{
		if (idx == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		idx++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - frees a linked list
 * @h_ptr: address of pointer the node to be freed
 */

void free_list(list_t **h_ptr)
{
	list_t *node, *next_node, *head;

	if (!h_ptr || !*h_ptr)
		return;
	head = *h_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*h_ptr = NULL;
}

/**
 * node_starts_with - Searches for a node with
 *			a string that starts with a prefix.
 * @node: Pointer to the head of the linked list.
 * @prefix: Prefix to search for at the beginning of the strings.
 * @c: Character condition to match (or -1 to match any character).
 * Return: the matched node or null.
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *ptr = NULL;

	while (node)
	{
		ptr = start_with(node->str, prefix);
		if (ptr && ((c == -1) || (*ptr == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - Finds the index of a node within a linked list.
 * @head: Pointer to the head of the linked list.
 * @node: Pointer to the node whose index is to be found.
 * Return: index of node
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	ssize_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}

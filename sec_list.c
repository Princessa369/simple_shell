#include "simpshell.h"

/**
 * list_len - this will check the length of linked list
 * @h: this is the pointer to the first node
 * Return: list size
 */
size_t list_len(const list_t *h)
{
	size_t k = 0;

	while (h)
	{
		h = h->next;
		k++;
	}
	return (k);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *fesnode = head;
	size_t k = list_len(head), l;
	char **strs;
	char *str;

	if (!head || !k)
		return (NULL);
	strs = malloc(sizeof(char *) * (k + 1));
	if (!strs)
		return (NULL);
	for (k = 0; fesnode; fesnode = fesnode->next, k++)
	{
		str = malloc(_strlen(fesnode->str) + 1);
		if (!str)
		{
			for (l = 0; l < k; l++)
				free(strs[l]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, fesnode->str);
		strs[k] = str;
	}
	strs[k] = NULL;
	return (strs);
}

/**
 * print_list - this will print all elements of a list_t linked list
 * @h: pointer to first node
 * Return: list size
 */
size_t print_list(const list_t *h)
{
	size_t k = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		k++;
	}
	return (k);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: pointer to head of list
 * @prefix: string to match
 * @c: the next character after prefix to match
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets a node index
 * @head: pointer to head of list
 * @node: pointer to node
 * Return: -1 or node index
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t k = 0;

	while (head)
	{
		if (head == node)
			return (k);
		head = head->next;
		k++;
	}
	return (-1);
}

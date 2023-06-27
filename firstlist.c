#include "simpshell.h"

/**
 * add_node - this will add a node to the start of the list
 * @head: this is the address of pointer to the head node
 * @str: pointer to the string field of node
 * @num: node index used.
 * Return: list size
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *ano_head;

	if (!head)
		return (NULL);
	ano_head = malloc(sizeof(list_t));
	if (!ano_head)
		return (NULL);
	_memset((void *)ano_head, 0, sizeof(list_t));
	ano_head->num = num;
	if (str)
	{
		ano_head->str = _strdup(str);
		if (!ano_head->str)
		{
			free(ano_head);
			return (NULL);
		}
	}
	ano_head->next = *head;
	*head = ano_head;
	return (ano_head);
}

/**
 * add_node_end - this will add a node to the end of the list
 * @head: this is the address of pointer to the head node
 * @str: pointer to the string field of node
 * @num: node index used.
 * Return: list size
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *sec_node, *fesnode;

	if (!head)
		return (NULL);

	fesnode = *head;
	sec_node = malloc(sizeof(list_t));
	if (!sec_node)
		return (NULL);
	_memset((void *)sec_node, 0, sizeof(list_t));
	sec_node->num = num;
	if (str)
	{
		sec_node->str = _strdup(str);
		if (!sec_node->str)
		{
			free(sec_node);
			return (NULL);
		}
	}
	if (fesnode)
	{
		while (fesnode->next)
			fesnode = fesnode->next;
		fesnode->next = sec_node;
	}
	else
		*head = sec_node;
	return (sec_node);
}

/**
 * print_list_str - this prints only the string element of a list_t linked list
 * @h: pointer to the first node
 * Return: list size
 */
size_t print_list_str(const list_t *h)
{
	size_t p = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		p++;
	}
	return (p);
}

/**
 * delete_node_at_index - this will delete node at a given index
 * @head: this is the address of pointer to the first node
 * @index: node index to be deleted
 * Return: on failure 0, on success 1.
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *fesnode, *prv_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		fesnode = *head;
		*head = (*head)->next;
		free(fesnode->str);
		free(fesnode);
		return (1);
	}
	fesnode = *head;
	while (fesnode)
	{
		if (i == index)
		{
			prv_node->next = fesnode->next;
			free(fesnode->str);
			free(fesnode);
			return (1);
		}
		i++;
		prv_node = fesnode;
		fesnode = fesnode->next;
	}
	return (0);
}

/**
 * free_list - this will free all nodes of a list
 * @head_ptr: this is the address of pointer to the head node
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *fesnode, *sec_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	fesnode = head;
	while (fesnode)
	{
		sec_node = fesnode->next;
		free(fesnode->str);
		free(fesnode);
		fesnode = sec_node;
	}
	*head_ptr = NULL;
}

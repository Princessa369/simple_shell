#include "simpshell.h"

/**
 * bfree - this will free a pointer and NULL the address
 * @ptr: address of the pointer to free
 * Return: if freed 1, else 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

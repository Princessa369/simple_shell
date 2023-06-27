#include "simpshell.h"

/**
 * input_buf - buffers chained commands
 * @info: struct parameter
 * @buf: buffer address
 * @len: address of length variable
 * Return: read bytes
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t n = 0;
	size_t lent = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		n = getline(buf, &lent, stdin);
#else
		n = _getline(info, buf, &lent);
#endif
		if (n > 0)
		{
			if ((*buf)[n - 1] == '\n')
			{
				(*buf)[n - 1] = '\0'; /* removes trailing newline */
				n--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = n;
				info->cmd_buf = buf;
			}
		}
	}
	return (n);
}

/**
 * get_input - gets a line without the newline
 * @info: struct parameter
 * Return: read bytes
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' is the command chain buffer */
	static size_t k, t, lent;
	ssize_t i = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	i = input_buf(info, &buf, &lent);
	if (i == -1) /* EOF */
		return (-1);
	if (lent) /* we have some commands left in the chain buffer */
	{
		t = k; /* init new iterator to current buff position */
		p = buf + k;
		check_chain(info, buf, &t, k, lent);
		while (t < lent) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &t))
				break;
			t++;
		}

		k = t + 1; /* increment past nulled ';'' */
		if (k >= lent) /* reached end of buffer? */
		{
			k = lent = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* passes the pointer to the current position of the command */
		return (_strlen(p)); /* will return the length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (i); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @info: struct parameter
 * @buf: buffer to be read
 * @i: size
 * Return: fit
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t fit = 0;

	if (*i)
		return (0);
	fit = read(info->readfd, buf, READ_BUF_SIZE);
	if (fit >= 0)
		*i = fit;
	return (fit);
}

/**
 * _getline - this function gets the next line of input from STDIN
 * @info: struct parameter
 * @ptr: pointer to buffer's address, preallocated or NULL
 * @length: preallocated ptr buffer size if it is not NULL
 * Return: sline
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t j, lent;
	size_t k;
	ssize_t r = 0, sline = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		sline = *length;
	if (j == lent)
		j = lent = 0;

	r = read_buf(info, buf, &lent);
	if (r == -1 || (r == 0 && lent == 0))
		return (-1);

	c = _strchr(buf + j, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : lent;
	new_p = _realloc(p, sline, sline ? sline + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (sline)
		_strncat(new_p, buf + j, k - j);
	else
		_strncpy(new_p, buf + j, k - j + 1);

	sline += k - j;
	j = k;
	p = new_p;

	if (length)
		*length = sline;
	*ptr = p;
	return (sline);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

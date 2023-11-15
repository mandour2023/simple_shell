#include "shell.h"

/**
 * in_buf - buffers chained commands
 * @inf: parameter struct
 * @bf: address of buffer
 * @ln: address of len var
 *
 * Return: bytes read
 */
ssize_t in_buf(info_t *inf, char **bf, size_t *ln)
{
	ssize_t r = 0;
	size_t ln_p = 0;

	if (!*ln) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)inf->cmd_buf);*/
		free(*bf);
		*bf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(bf, &ln_p, stdin);
#else
		r = _getline(inf, bf, &ln_p);
#endif
		if (r > 0)
		{
			if ((*bf)[r - 1] == '\n')
			{
				(*bf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			inf->linecount_flag = 1;
			remove_comments(*bf);
			build_history_list(inf, *bf, inf->histcount++);
			/* if (_strchr(*bf, ';')) is this a command chain? */
			{
				*ln = r;
				inf->cmd_buf = bf;
			}
		}
	}
	return (r);
}

/**
 * gt_in - gets a line minus the newline
 * @inf: parameter struct
 *
 * Return: bytes read
 */
ssize_t gt_in(info_t *inf)
{
	static char *bf; /* the ';' command chain buffer */
	static size_t i, j, ln;
	ssize_t r = 0;
	char **bf_p = &(inf->arg), *p;

	_putchar(BUF_FLUSH);
	r = in_buf(inf, &bf, &ln);
	if (r == -1) /* EOF */
		return (-1);
	if (ln)	/* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = bf + i; /* get pointer for return */

		check_chain(inf, bf, &j, i, ln);
		while (j < ln) /* iterate to semicolon or end */
		{
			if (is_chain(inf, bf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= ln) /* reached end of buffer? */
		{
			i = ln = 0; /* reset position and length */
			inf->cmd_buf_type = CMD_NORM;
		}

		*bf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*bf_p = bf; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
}

/**
 * rd_buf - reads a buffer
 * @inf: parameter struct
 * @bf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t rd_buf(info_t *inf, char *bf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(inf->readfd, bf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _gtline - gets the next line of input from STDIN
 * @inf: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _gtline(info_t *inf, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, ln;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == ln)
		i = ln = 0;

	r = rd_buf(inf, buf, &ln);
	if (r == -1 || (r == 0 && ln == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : ln;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sintHandler - blocks ctrl-C
 * @sNum: the signal number
 *
 * Return: void
 */
void sintHandler(__attribute__((unused))int sNum)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */

ssize_t buff_INput(info_t *info, char **buff, size_t *var_len)
{
	ssize_t r = 0;
	size_t len_buff = 0;

	if (!*var_len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buff, &len_buff, stdin);
#else
		r = line_gets(info, buff, &len_buff);
#endif
		if (r > 0)
		{
			if ((*buff)[r - 1] == '\n')
			{
				(*buff)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			comment_eliminate(*buff);
			build_MYhistoryList(info, *buff, info->histcount++);

			{
				*var_len = r;
				info->cmd_buff = buff;
			}
		}
	}
	return (r);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */

ssize_t input_get(info_t *info)
{
	static char *buff;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buff_p = &(info->arg), *p;

	_putchar(BUFF_FLUSH);
	r = buff_INput(info, &buff, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buff + i;

		check_ischain(info, buff, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (check_BUFFchain(info, buff, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			info->cmd_buff_type = CMD_NORM;
		}

		*buff_p = p;
		return (str_len(p));
	}

	*buff_p = buff;
	return (r); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */

ssize_t buff_READ(info_t *info, char *buff, size_t *i)
{
	ssize_t readd = 0;

	if (*i)
		return (0);
	readd = read(info->readfileDes, buff, READ_BUFF_SIZE);
	if (readd >= 0)
		*i = readd;
	return (readd);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */

int line_gets(info_t *info, char **ptr, size_t *length)
{
	static char buff[READ_BUFF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_ptr = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = buff_READ(info, buff, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buff + i, '\n');
	k = c ? 1 + (unsigned int)(c - buff) : len;
	new_ptr = New_alloc(p, s, s ? s + k : k + 1);
	if (!new_ptr)
		return (p ? free(p), -1 : -1);

	if (s)
		_strNcon(new_ptr, buff + i, k - i);
	else
		_strNcpy(new_ptr, buff + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_ptr;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */

void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFF_FLUSH);
}

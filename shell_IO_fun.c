#include "shell.h"

/**
 * get_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *getSHELL_historyFile(info_t *info)
{
	char *buff, *dir;

	dir = get_MYenviornment(info, "HOME=");
	if (!dir)
		return (NULL);
	buff = malloc(sizeof(char) * (str_len(dir) + str_len(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	str_con(buff, dir);
	str_con(buff, "/");
	str_con(buff, HIST_FILE);
	return (buff);
}

/**
 * write_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */

int write_SHELLhistory(info_t *info)
{
	ssize_t filedes;
	char *filename = getSHELL_historyFile(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	filedes = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	
	if (filedes == -1)
		return (-1);
	
	for (node = info->history; node; node = node->next)
	{
		puts_fileDes(node->str, filedes);
		puts_fileDes("\n", filedes);
	}
	puts_fileDes(BUFF_FLUSH, filedes);
	close(filedes);
	return (1);
}

/**
 * read_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */

int read_SHELLhistory(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t filedes, rdlen, filesize = 0;
	struct stat st;
	char *buff = NULL, *file_name = getSHELL_historyFile(info);

	if (!file_name)
		return (0);

	filedes = open(file_name, O_RDONLY);
	free(file_name);
	
	if (filedes == -1)
		return (0);
	
	if (!fstat(filedes, &st))
		filesize = st.st_size;
	
	if (filesize < 2)
		return (0);
	buff = malloc(sizeof(char) * (filesize + 1));
	
	if (!buff)
		return (0);
	rdlen = read(filedes, buff, filesize);
	buff[filesize] = 0;
	
	if (rdlen <= 0)
		return (free(buff), 0);
	close(filedes);
	for (i = 0; i < filesize; i++)
		if (buff[i] == '\n')
		{
			buff[i] = 0;
			build_MYhistoryList(info, buff + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_MYhistoryList(info, buff + last, linecount++);
	
	free(buff);
	info->histcount = linecount;
	
	while (info->histcount-- >= HIST_MAX)
		NodeRemove(&(info->history), 0);
	
	recount_MYhistory(info);
	
	return (info->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */

int build_MYhistoryList(info_t *info, char *buff, int lineCount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	node_endADD(&node, buff, lineCount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */

int recount_MYhistory(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->node_num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}

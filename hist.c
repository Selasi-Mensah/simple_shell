#include "shell.h"

/**
 * hist_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *hist_file(myInfoType *custominfo)
{
	char *command_buffer, *d;

	d = customGetenv(custominfo, "HOME=");
	if (!d)
		return (NULL);
	command_buffer = malloc(sizeof(char) * (_stringLength(d) + _stringLength(HISTORY_FILE) + 2));
	if (!command_buffer)
		return (NULL);
	command_buffer[0] = 0;
	_strcpy_custom(command_buffer, d);
	_stringConcatenate(command_buffer, "/");
	_stringConcatenate(command_buffer, HISTORY_FILE);
	return (command_buffer);
}

/**
 * hist_pen_write - creates a file, or appends to an existing file
 * @custominfo: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int hist_pen_write(myInfoType *custominfo)
{
	ssize_t fd;
	char *filename = hist_file(custominfo);
	list_a *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = custominfo->history_node; node; node = node->next)
	{
		custom_puts_to_fd(node->str, fd);
		custom_write_to_fd('\n', fd);
	}
	custom_write_to_fd(BUFFER_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * hist_read - reads history from file
 * @custominfo: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int hist_read(myInfoType *custominfo)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, len_read, filesize = 0;
	struct stat sd;
	char *buffer = NULL, *filename = hist_file(custominfo);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &sd))
		filesize = sd.st_size;
	if (filesize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (filesize + 1));
	if (!buffer)
		return (0);
	len_read = read(fd, buffer, filesize);
	buffer[filesize] = 0;
	if (len_read <= 0)
		return (free(buffer), 0);
	close(fd);
	for (i = 0; i < filesize; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			bhistlist(custominfo, buffer + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		bhistlist(custominfo, buffer + last, linecount++);
	free(buffer);
	custominfo->history_line_count = linecount;
	while (custominfo->history_line_count-- >= HISTORY_MAXIMUM)
		delete_node_at_index(&(custominfo->history_node), 0);
	history_renumbering(custominfo);
	return (custominfo->history_line_count);
}

/**
 * bhistlist - adds entry to a history linked list
 * @custominfo: Structure containing potential arguments. Used to maintain
 * @buffer: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int bhistlist(myInfoType *custominfo, char *buffer, int linecount)
{
	list_a *node = NULL;

	if (custominfo->history_node)
		node = custominfo->history_node;
	add_node_end(&node, buffer, linecount);

	if (!custominfo->history_node)
		custominfo->history_node = node;
	return (0);
}

/**
 * history_renumbering - renumbers the history linked list after changes
 * @custominfo: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int history_renumbering(myInfoType *custominfo)
{
	list_a *node = custominfo->history_node;
	int i = 0;

	while (node)
	{
		node->n = i++;
		node = node->next;
	}
	return (custominfo->history_line_count = i);
}

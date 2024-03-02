#include "shell.h"


/**
 * is_executable - determines if a file is an executable command
 * @custominfo: the info struct
 * @pathway: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_executable(myInfoType *custominfo, char *pathway)
{
	struct stat cs;

	(void)custominfo;
	if (!pathway || stat(pathway, &cs))
		return (0);

	if (cs.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * multiple - dmakes characters double
 * @pathwaystr: the PATH string
 * @end: starting index
 * @begin: stopping index
 *
 * Return: pointer to new buffer
 */
char *multiple(char *pathwaystr, int begin, int end)
{
	static char buf[1024];
	int a = 0, k = 0;

	for (k = 0, a = begin; a < end; a++)
		if (pathwaystr[a] != ':')
			buf[k++] = pathwaystr[a];
	buf[k] = 0;
	return (buf);
}

/**
 * pathing - searches this command in the PATH string
 * @custominfo: the info struct
 * @pathwaystr: the PATH string
 * @command: the command to find
 *
 * Return: full path of command if found or NULL
 */
char *pathing(myInfoType *custominfo, char *pathwaystr, char *command)
{
	int i = 0, currentPosition = 0;
	char *path;

	if (!pathwaystr)
		return (NULL);
	if ((_stringLength(command) > 2) && _startsWith(command, "./"))
	{
		if (is_executable(custominfo, command))
			return (command);
	}
	while (1)
	{
		if (!pathwaystr[i] || pathwaystr[i] == ':')
		{
			path = multiple(pathwaystr, currentPosition, i);
			if (!*path)
				_stringConcatenate(path, command);
			else
			{
				_stringConcatenate(path, "/");
				_stringConcatenate(path, command);
			}
			if (is_executable(custominfo, path))
				return (path);
			if (!pathwaystr[i])
				break;
			currentPosition = i;
		}
		i++;
	}
	return (NULL);
}

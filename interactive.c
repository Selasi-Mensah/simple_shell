#include "shell.h"

/**
 * interactive - checks if shell is in interactive mode
 * @customInfo: struct to work with
 * 
 * Return: 1 if in interactive mode or 0
*/

int interactive(myInfoType *customInfo)
{
    return (isatty(STDIN_FILENO) && customInfo ->read_file_descriptor <= 2);
}


/**
 * delim - checks if character is a delimeter
 * @c: the char to check
 * @char_delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int delim(char c, char *char_delim)
{
	while (*char_delim)
		if (*char_delim++ == c)
			return (1);
	return (0);
}

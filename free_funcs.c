#include "hsh4copy.h"

/**
 * _free_argv - frees all memory allocated for LinePtr_copy.
 * @LinePtr_copy: copy of input string
 * Return: Nothing.
 */

void _free_argv(char **LinePtr_copy)
{
	size_t j = 0;

	if (LinePtr_copy == NULL)
		return;

	while (LinePtr_copy[j])
	{
		free(LinePtr_copy[j]);
		j++;
	}

	if (LinePtr_copy[j] == NULL)
	{
		free(LinePtr_copy[j]);
	}

	free(LinePtr_copy);
}



/**
 * _free_before_exit - frees all memory allocated and exit.
 * @LinePtr_copy: copy of input string
 * Return: Nothing.
 */

void _free_before_exit(char **LinePtr_copy)
{
	size_t i = 0;

	if (LinePtr_copy == NULL)
		return;

	while (LinePtr_copy[i])
	{
		free(LinePtr_copy[i]);
		i++;
	}

	if (LinePtr_copy[i] == NULL)
	{
		free(LinePtr_copy[i]);
	}

	free(LinePtr_copy);
	exit(1);
}

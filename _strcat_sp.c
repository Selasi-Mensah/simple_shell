#include "hsh4copy.h"

/**
 * _strcat_sp - Concatenates two strings.
 * @destin: An input string.
 * @source: An input string.
 * Return: A pointer to the resulting string.
 */

char *_strcat_sp(char *destin, char *source)
{
	char *temp = destin;
	int i = 0, j = 0;

	while (destin[i])
	{
		i++;
	}

	destin[i] = '/';
	i++;

	while (source[j])
	{
		destin[i] = source[j];
		i++;
		j++;
	}
	return (temp);
}

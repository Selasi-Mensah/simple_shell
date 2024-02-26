#include "hsh4copy.h"

/**
 * _strcpy - Copies a string and paste to another string.
 * @destin: string destination
 * @source: string source
 * Return: A pointer to copied string.
 */

char *_strcpy(char *destin, char *source)
{
	char *tempor = destin;
	int i = 0;

	while (source[i])
	{
		destin[i] = source[i];
		i++;
	}
	destin[i] = '\0';

	return (tempor);
}

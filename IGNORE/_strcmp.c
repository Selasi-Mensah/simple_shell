#include "hsh4copy.h"

/**
 * _strcmp - A funtion that compares two strings.
 * @s1: first string
 * @s2: second string
 * Return: 1 if strings are the same, 0 if not.
 */

int _strcmp(char *s1, char *s2)
{
	unsigned int i = 0;

	while (s1[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

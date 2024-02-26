#include "hsh4copy.h"

/**
 * _strncmp - compates n characters in 2 strings
 * @s1: first string
 * @s2: 2nd string
 * @n: number of bytes to compare
 * Return: 0 if it's a match and -1 or 1 if not
 */

int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++)
	{
		if (s1[i] != s2[i])
		{
			return ((s1[i] < s2[i]) ? -1 : 1);
		}
		else if (s1[i] == '\0')
		{
			return (0);
		}
	}
	return (0);
}

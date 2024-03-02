#include "hsh4copy.h"

/**
 * _puts - prints a string to stdout
 * @s: pointer
 * Return: nothing
 */
void _puts(char *s)
{
	while (*s != 0)
	{
		write(1, &(*s), 1);
		s++;
	}
}

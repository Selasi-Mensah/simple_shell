#include "shell.h"

/**
 **_memset - fills memory with a constant byte
 *@s: the pointer to the memory area
 *@b: the byte to fill *s with
 *@n: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}


/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @oldie: byte size of previous block
 * @newbie: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int oldie, unsigned int newbie)
{
	char *p;

	if (!ptr)
		return (malloc(newbie));
	if (!newbie)
		return (free(ptr), NULL);
	if (newbie == oldie)
		return (ptr);

	p = malloc(newbie);
	if (!p)
		return (NULL);

	oldie = oldie < newbie ? oldie : newbie;
	while (oldie--)
		p[oldie] = ((char *)ptr)[oldie];
	free(ptr);
	return (p);
}

#include "shell.h"

/**
 * **spiltString - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @char_delim: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **spiltString(char *string, char *char_delim)
{
	int a, b, c, f, numwords = 0;
	char **s;

	if (string == NULL || string[0] == 0)
		return (NULL);
	if (!char_delim)
		char_delim = " ";
	for (a = 0; string[a] != '\0'; a++)
		if (!delim(string[a], char_delim) && (delim(string[a + 1], char_delim) || !string[a + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < numwords; b++)
	{
		while (delim(string[a], char_delim))
			a++;
		c = 0;
		while (!delim(string[a + c], char_delim) && string[a + c])
			c++;
		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (f = 0; f < c; f++)
			s[b][f] = string[a++];
		s[b][f] = 0;
	}
	s[b] = NULL;
	return (s);
}

/**
 * **spiltString2 - splits a string into words
 * @string: the input string
 * @char_delim: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **spiltString2(char *string, char char_delim)
{
	int i, b, c, f, numwords = 0;
	char **s;

	if (string == NULL || string[0] == 0)
		return (NULL);
	for (i = 0; string[i] != '\0'; i++)
		if ((string[i] != char_delim && string[i + 1] == char_delim) ||
		    (string[i] != char_delim && !string[i + 1]) || string[i + 1] == char_delim)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, b = 0; b < numwords; b++)
	{
		while (string[i] == char_delim && string[i] != char_delim)
			i++;
		c = 0;
		while (string[i + c] != char_delim && string[i + c] && string[i + c] != char_delim)
			c++;
		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (f = 0; f < c; f++)
			s[b][f] = string[i++];
		s[b][f] = 0;
	}
	s[b] = NULL;
	return (s);
}

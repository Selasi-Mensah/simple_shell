#include "hsh4copy.h"

/**
 * _handle - handle Ctr + C signal.
 * @signals: The signal to handle.
 * Return:
 */

void _handle(int signals)
{
	(void)signals;
	write(1, "RN_SHELL $ ", 11);
}

/**
 * _shell_prompt - prints the prompt
 *
 * Return: Nothing.
 */

void _shell_prompt(void)
{
	if (isatty(0))
		write(1, "RN_SHELL $ ", 11);
}

/**
 * check_spaces - checks if the user input only spaces.
 * @LinePtr: The pointer to input string.
 * Return: 1 on success, 0 on failure
 */
int check_spaces(char *LinePtr)
{
	int i = 0;

	LinePtr[_strlen(LinePtr) - 1] = '\0';
	while (LinePtr[i] != '\0')
	{
		if (LinePtr[i] != ' ')
			return (0);
		i++;

	}
	return (1);
}

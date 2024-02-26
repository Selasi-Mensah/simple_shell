#include "hsh4copy.h"


/**
 * _EOF_case - checks if EOF character was encountered
 * @LinePtr: The pointer to the input string.
 * Return: Nothing
 */

void _EOF_case(char *LinePtr)
{
	if (LinePtr)
	{
		free(LinePtr);
		LinePtr = NULL;
	}

	if (isatty(0))
		write(1, "\n", 1);

	free(LinePtr);
	exit(EXIT_SUCCESS);
}

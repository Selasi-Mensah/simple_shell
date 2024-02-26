#include "hsh4copy.h"

/**
 * main - Entry point
 * Description: A function that creates a simple shell
 * @ac: argument count
 * @av: Array of strings
 * @env: Array of environment variables
 * Return: Always 0.
 */

int main(int ac, char **av, char **env)
{
	char *LinePtr = NULL, **LinePtr_copy = NULL;
	ssize_t numchars_read = 0;
	size_t line_size = 0, prm_i = 0;

	while (1)
	{
		prm_i = prm_i + 1;
		_shell_prompt();
		numchars_read = getline(&LinePtr, &line_size, stdin);
		if (numchars_read == -1)
			_EOF_case(LinePtr);
		else if (*LinePtr == '\n' || check_spaces(LinePtr))
			free(LinePtr);
		else
		{
			LinePtr_copy = _parse_token(LinePtr, " \t\n\0");
			free(LinePtr);
			if (_strcmp(LinePtr_copy[0], "exit") == 0)
				_exit_shell(LinePtr_copy);
			else if (_strcmp(LinePtr_copy[0], "env") == 0)
				_envir_print(LinePtr_copy, env);
			else if (_strcmp(LinePtr_copy[0], "cd") == 0)
				_change_dir_func(LinePtr_copy[1], env);
			else
				_invok_child(LinePtr_copy, av[0], env, prm_i);
		}
		fflush(stdin);
		LinePtr = NULL, line_size = 0;
	}
	(void)ac;
	return (EXIT_SUCCESS);
}

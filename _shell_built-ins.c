#include "hsh4copy.h"

/**
 * _envir_print - A function that prints all enviromental variables.
 * @LinePtr_copy: Commands from user
 * @env: The pointer to enviromental variables.
 * Return:
 */

void _envir_print(char **LinePtr_copy, char **env)
{
	size_t l = 0, len = 0;

	while (env[l])
	{
		len = _strlen(env[l]);

		write(1, env[l], len);
		write(1, "\n", 1);

		l++;
	}
	_free_argv(LinePtr_copy);
}

/**
 * _exit_shell - Exits the shell if "exit" is encountered
 * @LinePtr_copy: The pointer to tokenized LinePtr_copy.
 * Return: Nothing.
 */

void _exit_shell(char **LinePtr_copy)
{
	int sta_tus = 0;

	if (LinePtr_copy[1] == NULL)
	{
		if (sta_tus == 2)
		{
			_free_argv(LinePtr_copy);
			exit(2);
		}
		else
		{
			_free_argv(LinePtr_copy);
			exit(0);
		}
	}
	else
	{
		sta_tus = _atoi(LinePtr_copy[1]);
		_free_argv(LinePtr_copy);
		exit(sta_tus);
	}

}

/**
 * _change_dir_func - changes working directory.
 * @path: The new current working directory.
 * @env: Array of environment variables
 * Return: 0 on success, -1 on failure.
 */

int _change_dir_func(char *path, char **env)
{
	char *new_dir, *current_dir/* *buffer = NULL */;

	if (path == NULL || _strcmp(path, "~") == 0)
		new_dir = _get_home_dir(env);
	else if (_strcmp(path, "-") == 0)
		new_dir = _get_oldpwd(env);
	else
		new_dir = path;

	if (chdir(new_dir) != 0)
		perror("Error");
	else
	{
		current_dir = getcwd(NULL, 0);
		setenv("OLDPWD", getenv("PWD"), 1);
		setenv("PWD", current_dir, 1);
		if (current_dir != NULL)
			free(current_dir);
	}
	free(path);
	return (0);
}


/**
 * _get_home_dir - Gets the value of the
 * HOME enviromental variable.
 * @env: Array of enviromental variables.
 * Return: the path of the home dir
 */

char *_get_home_dir(char **env)
{
	char *home = NULL;
	size_t i = 0;

	while (env[i])
	{
		if (strncmp(env[i], "HOME=", 5) == 0)
		{
			home = &env[i][5];
			break;
		}
		i++;
	}

	return (home);
}


/**
 * _get_oldpwd - Gets the value of the
 * OLDPWD enviromental variable.
 * @env: Array of enviromental variables.
 * Return: OLDPWD path
 */

char *_get_oldpwd(char **env)
{
	char *home = NULL;
	size_t i = 0;

	while (env[i])
	{
		if (strncmp(env[i], "OLDPWD=", 7) == 0)
		{
			home = &env[i][7];
			break;
		}
		i++;
	}

	return (home);
}

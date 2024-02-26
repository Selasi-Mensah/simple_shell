#include "hsh4copy.h"


/**
 * _invok_child - makes child process
 * @LinePtr_copy: The pointer to tokenized LinePtr_copy.
 * @name: The shell's name.
 * @env: Array of enviromental variables.
 * @prm_i: Prompt count.
 * Return: Nothing.
 */

void _invok_child(char **LinePtr_copy, char *name, char **env, size_t prm_i)
{
	pid_t pid = 0;
	int status = 0, wait_err = 0;

	pid = fork();
	if (pid < 0)
	{
		perror("Error: ");
		_free_before_exit(LinePtr_copy);
	}
	else if (pid == 0)
	{
		_execmd(LinePtr_copy, name, env, prm_i);
		/*_free_argv(LinePtr_copy);*/

	}
	else
	{
		wait_err = waitpid(pid, &status, 0);
		if (wait_err < 0)
		{
			_free_before_exit(LinePtr_copy);
		}
		_free_argv(LinePtr_copy);
	}
}

/**
 * _execmd - A function that executes a LinePtr_copy.
 * @LinePtr_copy: The pointer to tokenized LinePtr_copy.
 * @name: The name of the shell.
 * @env: The pointer to the enviromental variables.
 * @prm_i: Number of executed prm_i.
 * Return: Nothing.
 */
void _execmd(char **LinePtr_copy, char *name, char **env, size_t prm_i)
{
	char **pathvar = NULL, *fullcmdpath = NULL;
	struct stat buf;
	unsigned int i = 0;

	if (stat(LinePtr_copy[0], &buf) == 0)
	{
		if (execve(LinePtr_copy[0], LinePtr_copy, env) < 0)
		{
			/*perror(name);*/
			_free_before_exit(LinePtr_copy);
		}
	}
	else
	{
		pathvar = _get_pathtok(env);
		while (pathvar[i])
		{
			fullcmdpath = _strcat_sp(pathvar[i], LinePtr_copy[0]);
			i++;
			if (stat(fullcmdpath, &buf) == 0)
			{
				if (execve(fullcmdpath, LinePtr_copy, env) < 0)
				{
					/*perror(name);*/
					_free_argv(pathvar);
					_free_before_exit(LinePtr_copy);
				}
				return;
			}
		}
		_error_msg(name, prm_i, LinePtr_copy);
		/*(void)name; (void)prm_i;*/
		_free_argv(pathvar);
		_free_argv(LinePtr_copy);
		LinePtr_copy = NULL;
	}
}


/**
 * _error_msg - prints error messahe
 * @name: The name of the shell.
 * @prm_i: Number of prm_i.
 * @LinePtr_copy: The pointer to tokenized LinePtr_copy.
 * Return: Nothing.
 */

void _error_msg(char *name, size_t prm_i, char **LinePtr_copy)
{
	char c;

	/*perror(name);*/
	c = prm_i + '0';
	write(2, name, _strlen(name));
	write(2, ": ", 2);
	write(2, &c, 1);
	write(2, ": ", 2);
	write(2, LinePtr_copy[0], _strlen(LinePtr_copy[0]));
	write(2, ": not found\n", 12);
}


/**
 * _get_pathtok - Gets the full value from the
 * PATH enviromental variable.
 * @env: Array of enviromental variables.
 * Return: the directories listed in the
 * PATH environment variable.
 */

char **_get_pathtok(char **env)
{
	char *pathvalue = NULL, **pathvar = NULL;
	size_t k = 0;

	pathvalue = strtok(env[k], "=");
	while (env[k])
	{
		if (_strcmp(pathvalue, "PATH") == 0)
		{
			pathvalue = strtok(NULL, "\n");
			pathvar = _parse_token(pathvalue, ":");
			return (pathvar);
		}
		k++;
		pathvalue = strtok(env[k], "=");
	}
	return (NULL);
}


/**
 * _parse_token - A function that split and create a full string command.
 * @delimit: The delimiter for str.
 * @LinePtr: The pointer to input string.
 * Return: A string with full command.
 */

char **_parse_token(char *LinePtr, const char *delimit)
{
	char *token = NULL, **LinePtr_copy = NULL;
	size_t buffersize = 0;
	int i = 0;

	if (LinePtr == NULL)
		return (NULL);

	buffersize = _strlen(LinePtr);
	LinePtr_copy = malloc(sizeof(char *) * (buffersize + 1));
	if (LinePtr_copy == NULL)
	{
		perror("Unable to allocate LinePtr");
		free(LinePtr);
		_free_argv(LinePtr_copy);
		exit(EXIT_FAILURE);
	}
	token = strtok(LinePtr, delimit);
	while (token != NULL)
	{
		LinePtr_copy[i] = malloc(_strlen(token) + 1);
		if (LinePtr_copy[i] == NULL)
		{
			perror("Unable to allocate LinePtr");
			_free_argv(LinePtr_copy);
			free(LinePtr);
			return (NULL);
		}
		_strcpy(LinePtr_copy[i], token);
		token = strtok(NULL, delimit);
		i++;
	}
	LinePtr_copy[i] = NULL;
	return (LinePtr_copy);
}

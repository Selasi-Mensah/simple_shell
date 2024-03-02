#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int shell(myInfoType *custominfo, char **av)
{
	ssize_t nread = 0;
	int function_return = 0;

	while (nread != -1 && function_return != -2)
	{
		resetting(custominfo);
		if (interactive(custominfo))
			_puts_custom("$ ");
		custom_write_to_stderr(BUFFER_FLUSH);
		nread = get_commands(custominfo);
		if (nread != -1)
		{
			initiate_custom_info(custominfo, av);
			function_return = lookSysCommand(custominfo);
			if (function_return == -1)
				find_command(custominfo);
		}
		else if (interactive(custominfo))
			_putchar_custom('\n');
		free_command(custominfo, 0);
	}
	hist_pen_write(custominfo);
	free_command(custominfo, 1);
	if (!interactive(custominfo) && custominfo->execution_status)
		exit(custominfo->execution_status);
	if (function_return == -2)
	{
		if (custominfo->error_number == -1)
			exit(custominfo->execution_status);
		exit(custominfo->error_number);
	}
	return (function_return);
}

/**
 * lookSysCommand - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int lookSysCommand(myInfoType *custominfo)
{
	int a, function_ret = -1;
	customBuiltinTable tableau[] = {
		{"exit", exitingIsmine},
		{"env", envMine},
		{"help", helpMe},
		{"history", histmine},
		{"setenv", newSetenv},
		{"unsetenv",newUnsetenv},
		{"cd", chWorDir},
		{"alias", mimic_alias},
		{NULL, NULL}
	};

	for (a = 0; tableau[a].command_type; a++)
		if (_stringCompare(custominfo->argument_array[0], tableau[a].command_type) == 0)
		{
			custominfo->count_line_flag++;
			function_ret = tableau[a].command_function(custominfo);
			break;
		}
	return (function_ret);
}

/**
 * find_command - finds a command in PATH
 * @custominfo: the parameter & return info struct
 *
 * Return: void
 */
void find_command(myInfoType *custominfo)
{
	char *path = NULL;
	int a, b;

	custominfo->command_path_str = custominfo->argument_array[0];
	if (custominfo->count_line_flag == 1)
	{
		custominfo->line_number++;
		custominfo->count_line_flag = 0;
	}
	for (a = 0, b = 0; custominfo->argument_string[a]; a++)
		if (!delim(custominfo->argument_string[a], " \t\n"))
			b++;
	if (!b)
		return;

	path = pathing(custominfo, customGetenv(custominfo, "PATH="), custominfo->argument_array[0]);
	if (path)
	{
		custominfo->command_path_str = path;
		exec_cmd(custominfo);
	}
	else
	{
		if ((interactive(custominfo) || customGetenv(custominfo, "PATH=")
			|| custominfo->argument_array[0][0] == '/') && is_executable(custominfo, custominfo->argument_array[0]))
			exec_cmd(custominfo);
		else if (*(custominfo->argument_string) != '\n')
		{
			custominfo->execution_status = 127;
			display_custom_error(custominfo, "not found\n");
		}
	}
}

/**
 * exec_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void exec_cmd(myInfoType *custominfo)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(custominfo->command_path_str, custominfo->argument_array, get_environment(custominfo)) == -1)
		{
			free_command(custominfo, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(custominfo->execution_status));
		if (WIFEXITED(custominfo->execution_status))
		{
			custominfo->execution_status = WEXITSTATUS(custominfo->execution_status);
			if (custominfo->execution_status == 126)
				display_custom_error(custominfo, "Permission denied\n");
		}
	}
}

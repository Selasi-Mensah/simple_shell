#include "shell.h"

/**
 * exitingIsmine - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int exitingIsmine(myInfoType *custominfo)
{
	int checkExit;

	if (custominfo->argument_array[1])  /* If there is an exit arguement */
	{
		checkExit =  custom_atoi(custominfo->argument_array[1]);
		if (checkExit == -1)
		{
			custominfo->execution_status = 2;
			display_custom_error(custominfo, "Illegal number: ");
			custom_print_error_string(custominfo->argument_array[1]);
			custom_write_to_stderr('\n');
			return (1);
		}
		custominfo->error_number =  custom_atoi(custominfo->argument_array[1]);
		return (-2);
	}
	custominfo->error_number = -1;
	return (-2);
}

/**
 * chWorDir - changes the current directory of the process
 * @custominfo: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int chWorDir(myInfoType *custominfo)
{
	char *k, *dictry, buffer[1024];
	int ret_dictry;

	k = getcwd(buffer, 1024);
	if (!k)
		_puts_custom("TODO: >>getcwd failure emsg here<<\n");
	if (!custominfo->argument_array[1])
	{
		dictry = customGetenv(custominfo, "HOME=");
		if (!dictry)
			ret_dictry = /* TODO: what should this be? */
				chdir((dictry = customGetenv(custominfo, "PWD=")) ? dictry : "/");
		else
			ret_dictry = chdir(dictry);
	}
	else if (_stringCompare(custominfo->argument_array[1], "-") == 0)
	{
		if (!customGetenv(custominfo, "OLDPWD="))
		{
			_puts_custom(k);
			_putchar_custom('\n');
			return (1);
		}
		_puts_custom(customGetenv(custominfo, "OLDPWD=")), _putchar_custom('\n');
		ret_dictry = /* TODO: what should this be? */
			chdir((dictry = customGetenv(custominfo, "OLDPWD=")) ? dictry : "/");
	}
	else
		ret_dictry = chdir(custominfo->argument_array[1]);
	if (ret_dictry == -1)
	{
		display_custom_error(custominfo, "can't cd to ");
		custom_print_error_string(custominfo->argument_array[1]), custom_write_to_stderr('\n');
	}
	else
	{
		custom_set_environment_variable(custominfo, "OLDPWD", customGetenv(custominfo, "PWD="));
		custom_set_environment_variable(custominfo, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * helpMe - changes the current directory of the process
 * @custominfo: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int helpMe(myInfoType *custominfo)
{
	char **arg_arg;

	arg_arg = custominfo->argument_array;
	_puts_custom("help call works. Function not yet implemented \n");
	if (0)
		_puts_custom(*arg_arg); /* temp att_unused workaround */
	return (0);
}

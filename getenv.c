#include "shell.h"

/**
 * envMine - prints the current environment
 * @custominfo: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int envMine(myInfoType *custominfo)
{
	 print_custom_list(custominfo->environment_list);
	return (0);
}

/**
 * customGetenv - gets the value of an environ variable
 * @custominfo: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *customGetenv(myInfoType *custominfo, const char *name)
{
	list_a *node = custominfo->environment_list;
	char *e;

	while (node)
	{
		e = _startsWith(node->str, name);
		if (e && *e)
			return (e);
		node = node->next;
	}
	return (NULL);
}

/**
 * newSetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @custominfo: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int newSetenv(myInfoType *custominfo)
{
	if (custominfo->argument_count != 3)
	{
		custom_print_error_string("Incorrect number of arguements\n");
		return (1);
	}
	if (custom_set_environment_variable(custominfo, custominfo->argument_array[1], custominfo->argument_array[2]))
		return (0);
	return (1);
}

/**
 * newUnsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int newUnsetenv(myInfoType *custominfo)
{
	int a;

	if (custominfo->argument_count == 1)
	{
		custom_print_error_string("Too few arguements.\n");
		return (1);
	}
	for (a = 1; a <= custominfo->argument_count; a++)
		custom_unset_environment_variable(custominfo, custominfo->argument_array[a]);

	return (0);
}

/**
 * listOfenviroment - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int listOfenviroment(myInfoType *custominfo)
{
	list_a *node = NULL;
	size_t q;

	for (q = 0; environ[q]; q++)
		add_node_end(&node, environ[q], 0);
	custominfo->environment_list = node;
	return (0);
}

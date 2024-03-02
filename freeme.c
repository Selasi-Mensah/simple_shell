#include "shell.h"

/**
 * resetting - initializes myInfoType struct
 * @custom_info: struct address
 */
void resetting(myInfoType *custom_info)
{
	custom_info->argument_string = NULL;
	custom_info->argument_array = NULL;
	custom_info->command_path_str = NULL;
	custom_info->argument_count = 0;
}




/**
 * finallyfree - frees a string of strings
 * @ff: string of strings
 */
void finallyfree(char **ff)
{
	char **a = ff;

	if (!ff)
		return;
	while (*ff)
		free(*ff++);
	free(a);
}


#include "shell.h"

/**
 * bfree - frees a pointer and NULLs the address
 * @ptr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int pfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
#include "shell.h"


/**
 * initiate_custom_info - initializes myInfoTyoe struct
 * @info: struct address
 * @av: argument vector
 */
void initiate_custom_info(myInfoType *custominfo, char **av)
{
	int i = 0;

	custominfo->file_name_str = av[0];
	if (custominfo->argument_string)
	{
		custominfo->argument_array = spiltString(custominfo->argument_string, " \t");
		if (!custominfo->argument_array)
		{

			custominfo->argument_array = malloc(sizeof(char *) * 2);
			if (custominfo->argument_array)
			{
				custominfo->argument_array[0] = _strdup_custom(custominfo->argument_string);
				custominfo->argument_array[1] = NULL;
			}
		}
		for (i = 0; custominfo->argument_array && custominfo->argument_array[i]; i++)
			;
		custominfo->argument_count = i;

		r_alias(custominfo);
		r_vars(custominfo);
	}
}

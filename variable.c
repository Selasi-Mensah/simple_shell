#include "shell.h"

/**
 * chaining - test if current char in bufferfer is a chain delimeter
 * @custominfo: the parameter struct
 * @buffer: the char buffer
 * @p: address of current position in buffer
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int chaining(myInfoType *custominfo, char *buffer, size_t *p)
{
	size_t w = *p;

	if (buffer[w] == '|' && buffer[w + 1] == '|')
	{
		buffer[w] = 0;
		w++;
		custominfo->command_buffer_type = OR_COMMAND;
	}
	else if (buffer[w] == '&' && buffer[w + 1] == '&')
	{
		buffer[w] = 0;
		w++;
		custominfo->command_buffer_type = AND_COMMAND;
	}
	else if (buffer[w] == ';') /* found end of this command */
	{
		buffer[w] = 0; /* replace semicolon with null */
		custominfo->command_buffer_type = CHAIN_COMMAND;
	}
	else
		return (0);
	*p = w;
	return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @custominfo: the parameter struct
 * @buffer: the char bufferfer
 * @p: address of current position in buffer
 * @a: starting position in buffer
 * @length: length of buffer
 *
 * Return: Void
 */
void chainKeche(myInfoType *custominfo, char *buffer, size_t *p, size_t a, size_t length)
{
	size_t w = *p;

	if (custominfo->command_buffer_type == AND_COMMAND)
	{
		if (custominfo->execution_status)
		{
			buffer[a] = 0;
			w = length;
		}
	}
	if (custominfo->command_buffer_type == OR_COMMAND)
	{
		if (!custominfo->execution_status)
		{
			buffer[a] = 0;
			w = length;
		}
	}

	*p = w;
}

/**
 * r_alias - replaces an aliases in the tokenized string
 * @custominfo: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int r_alias(myInfoType *custominfo)
{
	int a;
	list_a *node;
	char *p;

	for (a = 0; a < 10; a++)
	{
		node = find_matching_node(custominfo->alias_node, custominfo->argument_array[0], '=');
		if (!node)
			return (0);
		free(custominfo->argument_array[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup_custom(p + 1);
		if (!p)
			return (0);
		custominfo->argument_array[0] = p;
	}
	return (1);
}

/**
 * r_vars - replaces vars in the tokenized string
 * @custominfo: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int r_vars(myInfoType *custominfo)
{
	int a = 0;
	list_a *node;

	for (a = 0; custominfo->argument_array[a]; a++)
	{
		if (custominfo->argument_array[a][0] != '$' || !custominfo->argument_array[a][1])
			continue;

		if (!_stringCompare(custominfo->argument_array[a], "$?"))
		{
			r_string(&(custominfo->argument_array[a]),
				_strdup_custom(custom_itoa(custominfo->execution_status, 10, 0)));
			continue;
		}
		if (!_stringCompare(custominfo->argument_array[a], "$$"))
		{
			r_string(&(custominfo->argument_array[a]),
				_strdup_custom(custom_itoa(getpid(), 10, 0)));
			continue;
		}
		node = find_matching_node(custominfo->environment_list, &custominfo->argument_array[a][1], '=');
		if (node)
		{
			r_string(&(custominfo->argument_array[a]),
				_strdup_custom(_strchr(node->str, '=') + 1));
			continue;
		}
		r_string(&custominfo->argument_array[a], _strdup_custom(""));

	}
	return (0);
}

/**
 * r_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int r_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

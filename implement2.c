#include "shell.h"

/**
 * histmine - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @custominfo: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int histmine(myInfoType *custominfo)
{
	print_custom_list(custominfo->history_node);
	return (0);
}

/**
 * aliasSetnot - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int aliasSetnot(myInfoType *custominfo, char *str)
{
	char *q, y;
	int rt;

	q = _strchr(str, '=');
	if (!q)
		return (1);
	y = *q;
	*q = 0;
	rt = delete_node_at_index(&(custominfo->alias_node),
		get_index_of_node(custominfo->alias_node, find_matching_node(custominfo->alias_node, str, -1)));
	*q = y;
	return (rt);
}

/**
 * set_alias - sets alias to string
 * @custominfo: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int aliasSet(myInfoType *custominfo, char *str)
{
	char *m;

	m = _strchr(str, '=');
	if (!m)
		return (1);
	if (!*++m)
		return (aliasSetnot(custominfo, str));

	aliasSetnot(custominfo, str);
	return (add_node_end(&(custominfo->alias_node), str, 0) == NULL);
}

/**
 * display_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int display_alias(list_a *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar_custom(*a);
		_putchar_custom('\'');
		_puts_custom(p + 1);
		_puts_custom("'\n");
		return (0);
	}
	return (1);
}

/**
 * mimic_alias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int mimic_alias(myInfoType *custominfo)
{
	int t = 0;
	char *m = NULL;
	list_a *node = NULL;

	if (custominfo->argument_count == 1)
	{
		node = custominfo->alias_node;
		while (node)
		{
			display_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (t = 1; custominfo->argument_array[t]; t++)
	{
		m = _strchr(custominfo->argument_array[t], '=');
		if (m)
			aliasSet(custominfo, custominfo->argument_array[t]);
		else
			display_alias(find_matching_node(custominfo->alias_node, custominfo->argument_array[t], '='));
	}

	return (0);
}

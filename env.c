#include "shell.h"

/**
 * get_environment - Retrieves the string array copy of our environment.
 * @custom_info: Structure containing potential arguments. Used to maintain
 *               a constant function prototype.
 * Return: The modified string array.
 */
char **get_environment(myInfoType*custom_info)
{
    while (!custom_info->custom_environment || custom_info->environment_changed_flag)
    {
        custom_info->custom_environment = linked_list_to_array(custom_info->environment_list);
        custom_info->environment_changed_flag = 0;
    }

    return custom_info->custom_environment;
}

/**
 * custom_unset_environment_variable - Removes an environment variable.
 * @custom_info: Structure containing potential arguments.
 * @var: The string representing the environment variable property.
 *
 * This function removes the specified environment variable from the linked list.
 *
 * Return: 1 on successful removal, 0 otherwise.
 */
int custom_unset_environment_variable(myInfoType *custom_info, char *var)
{
    list_a *current_node = custom_info->environment_list;
    size_t node_index = 0;
    char *property;

    /* Check if either the linked list or the environment variable string is NULL */
    if (!current_node || !var)
        return 0;

    /* Iterate through the linked list to find the specified environment variable */
    while (current_node)
    {
        /* Check if the current node's string starts with the specified variable string */
        property = _startsWith(current_node->str, var);
        if (property && *property == '=')
        {
            /* Delete the node at the current index and update the environment change flag */
            custom_info->environment_changed_flag = delete_node_at_index(&(custom_info->environment_list), node_index);
            node_index = 0;
            current_node = custom_info->environment_list;
            continue;
        }

        /* Move to the next node in the linked list */
        current_node = current_node->next;
        node_index++;
    }

    /* Return the environment change flag */
    return custom_info->environment_changed_flag;
}


/**
 * custom_set_environment_variable - Initializes a new environment variable
 *                                   or modifies an existing one.
 * @custom_info: Structure containing potential arguments.
 * @variable: The string representing the environment variable property.
 * @value: The string representing the environment variable value.
 *
 * This function initializes a new environment variable or modifies an existing one.
 *
 * Return: Always 0.
 */
int custom_set_environment_variable(myInfoType *custom_info, char *variable, char *value)
{
    char *buffer = NULL;
    list_a *current_node = custom_info->environment_list;
    char *property;

    /* Check if either the variable or value is NULL */
    if (!variable || !value)
        return 0;

    /* Allocate memory for the buffer to store the environment variable string */
    buffer = malloc(_stringLength(variable) + _stringLength(value) + 2);
    if (!buffer)
        return 1;

    /* Copy the variable and value strings into the buffer */
    _strcpy_custom(buffer, variable);
    _stringConcatenate(buffer, "=");
    _stringConcatenate(buffer, value);

    /* Iterate through the linked list to find and modify an existing variable */
    for (; current_node; current_node = current_node->next)
    {
        /* Check if the current node's string starts with the specified variable string */
        property = _startsWith(current_node->str, variable);
        if (property && *property == '=')
        {
            /* Free the existing string, update it with the new buffer, and set the environment change flag */
            free(current_node->str);
            current_node->str = buffer;
            custom_info->environment_changed_flag = 1;
            break;
        }
    }

    /* If no existing variable is found, add a new node at the end of the linked list with the new buffer */
    if (!current_node)
    {
        add_node_end(&(custom_info->environment_list), buffer, 0);
        custom_info->environment_changed_flag = 1;
    }

    /* Free the buffer */
    free(buffer);

    /* Return 0 */
    return 0;
}

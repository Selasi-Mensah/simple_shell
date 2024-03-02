#include "shell.h"

/**
 * list_len - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const list_a *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}


/**
 * linked_list_to_array - Converts a linked list of strings to an array of strings.
 * @head: Pointer to the first node of the linked list.
 *
 * Return: An array of strings or NULL on failure.
 */
char **linked_list_to_array(list_a *head)
{
    list_a *current_node = head;
    size_t list_length = list_len(head), i;
    char **string_array;
    char *current_string;

    if (!head || !list_length)
        return NULL;

    /* Allocate memory for the array of strings */
    string_array = malloc(sizeof(char *) * (list_length + 1));

    if (!string_array)
        return NULL;

    i = 0;

    while (current_node)
    {
        /* Allocate memory for the current string */ 
        current_string = malloc(_stringLength(current_node->str) + 1);

        if (!current_string)
        {
            /* Free memory in case of an error */
            while (i > 0)
                free(string_array[--i]);
            free(string_array);
            return NULL;
        }

        /* Copy the content of the current node's string to the newly allocated string */
        current_string = _strcpy_custom(current_string, current_node->str);

        /* Assign the newly created string to the array of strings at the current index */
        string_array[i++] = current_string;

        current_node = current_node->next;
    }

    /* Set the last element of the array to NULL to indicate the end of the array */
    string_array[i] = NULL;

    return string_array;
}


/**
 * print_custom_list - Prints all elements of a custom_list_t linked list.
 * @head: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t print_custom_list(const list_a *head)
{
    size_t count = 0;

    while (head)
    {
        _puts_custom(custom_itoa(head->n, 10, 0));
        _putchar_custom(':');
        _putchar_custom(' ');
        _puts_custom(head->str ? head->str : "(nil)");
        _puts_custom("\n");
        head = head->next;
        count++;
    }

    return count;
}


/**
 * find_matching_node - Returns the node whose string starts with a prefix.
 * @current_node: Pointer to the list head.
 * @prefix_to_match: String to match.
 * @next_char_to_match: The next character after the prefix to match.
 *
 * Return: The matching node or NULL.
 */
list_a *find_matching_node(list_a *current_node, char *prefix_to_match, char next_char_to_match)
{
    char *match_start = NULL;

    while (current_node)
    {
        match_start = _startsWith(current_node->str, prefix_to_match);
        if (match_start && ((next_char_to_match == -1) || (*match_start == next_char_to_match)))
            return current_node;
        current_node = current_node->next;
    }

    return NULL;
}


/**
 * get_index_of_node - Gets the index of a specific node in a linked list.
 * @list_head: Pointer to the head of the linked list.
 * @target_node: Pointer to the node whose index is to be found.
 *
 * Return: Index of the node or -1 if the node is not found.
 */
ssize_t get_index_of_node(list_a *list_head, list_a *target_node)
{
    size_t index = 0;

    while (list_head)
    {
        if (list_head == target_node)
            return (ssize_t)index;

        list_head = list_head->next;
        index++;
    }

    return -1;
}

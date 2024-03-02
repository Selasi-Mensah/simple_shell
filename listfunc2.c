#include "shell.h"


/**
 * add_node_at_start - Adds a node to the start of the list.
 * @head: Address of the pointer to the head node.
 * @str: String field of the node.
 * @num: Node index used by history.
 *
 * This function adds a new node to the start of the linked list.
 *
 * Return: Pointer to the new head of the list.
 */
list_a *add_node_at_start(list_a **head, const char *str, int num)
{
    list_a *new_node;
    if (!head)
        return NULL;
    new_node = malloc(sizeof(list_a));
    if (!new_node)
        return NULL;

    memset((void *)new_node, 0, sizeof(list_a));
    new_node->n = num;

    if (str)
    {
        new_node->str = _strdup_custom(str);
        if (!new_node->str)
        {
            free(new_node);
            return NULL;
        }
    }

    new_node->next = *head;
    *head = new_node;

    return new_node;
}

/**
 * add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_a *add_node_end(list_a **head, const char *str, int num)
{
	list_a *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_a));
	if (!new_node)
		return (NULL);
	memset((void *)new_node, 0, sizeof(list_a));
	new_node->n = num;
	if (str)
	{
		new_node->str = _strdup_custom(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}



/**
 * delete_node_at_index - Deletes a node at the given index.
 * @head: Address of the pointer to the first node.
 * @index: Index of the node to delete.
 *
 * This function deletes a node at the specified index in the linked list.
 *
 * Return: 1 on success, 0 on failure.
 */
int delete_node_at_index(list_a **head, unsigned int index)
{
    list_a *current_node, *previous_node;
    unsigned int i = 0;

    if (!head || !*head)
        return 0;

    if (index == 0)
    {
        current_node = *head;
        *head = (*head)->next;
        free(current_node->str);
        free(current_node);
        return 1;
    }

    current_node = *head;
    while (current_node)
    {
        if (i == index)
        {
            previous_node->next = current_node->next;
            free(current_node->str);
            free(current_node);
            return 1;
        }
        i++;
        previous_node = current_node;
        current_node = current_node->next;
    }

    return 0;
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_a **head_ptr)
{
	list_a *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}



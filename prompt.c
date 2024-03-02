#include "shell.h"

/**
 * character_flush - a function that displays a character to stdout
 * @c: character to display
 * 
 * Return: On success 1
 * On error, -1 is returned
*/
int character_flush(char c)
{
    /* static variable to maintain state across function calls*/
    static int i;
    static int buffer[WRITE_BUFFER_SIZE];

    /* check if the character is a buffer flush or is buffer is full*/
    if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
    {
        /* write to stdout*/
        write(1, buffer, i);
        /* reset to buffer index*/
        i = 0;
    }
    /* check if the character is not a buffer flush*/
    if (c != BUFFER_FLUSH)
    /* adds the character to the buffer and increment the index*/
        buffer[i++] = c;
    return (1);
}

/**
 * free_command - frees info_t struct fields
 * @custom_info: struct address
 * @all: true if freeing all fields
 */
void free_command(myInfoType *custom_info, int all)
{
	finallyfree(custom_info->argument_array);
	custom_info->argument_array = NULL;
	custom_info->command_path_str = NULL;
	if (all)
	{
		if (!custom_info->command_buffer_pointer)
			free(custom_info->argument_string);
		if (custom_info->environment_list)
			free_list(&(custom_info->environment_list));
		if (custom_info->history_node)
			free_list(&(custom_info->history_node));
		if (custom_info->alias_node)
			free_list(&(custom_info->alias_node));
		finallyfree(custom_info->custom_environment);
			custom_info->custom_environment = NULL;
		pfree((void **)custom_info->command_buffer_pointer);
		if (custom_info->read_file_descriptor > 2)
			close(custom_info->read_file_descriptor);
		_putchar_custom(BUFFER_FLUSH);
	}
}
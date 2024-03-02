#include "shell.h"


/**
 * custom_print_error_string - Prints a string to the error output.
 * @error_str: The string to be printed.
 *
 * This function prints the provided string to the error output.
 *
 * Return: Nothing.
 */
void custom_print_error_string(char *error_str)
{
    int index = 0;

    /*  Check if the string is NULL */
    if (!error_str)
        return;

    /*  Iterate through the characters in the string until null terminator is reached */
    while (error_str[index] != '\0')
    {
        /*  Call custom function to print each character to the error output */
        custom_write_to_stderr(error_str[index]);
        index++;
    }
}


/**
 * custom_write_to_stderr - Writes a character to the standard error stream.
 * @ch: The character to be written.
 *
 * This function writes the specified character to the standard error stream.
 *
 * Return: On success, returns 1. On error, returns -1, and errno is set appropriately.
 */
int custom_write_to_stderr(char ch)
{
    static int buffer_index;
    static char output_buffer[WRITE_BUFFER_SIZE];

    /*  Check if it's time to flush the buffer or if the buffer is full */
    if (ch == BUFFER_FLUSH || buffer_index >= WRITE_BUFFER_SIZE)
    {
        /* Write the buffer to the standard error stream */
        write(2, output_buffer, buffer_index);
        buffer_index = 0;
    }

    /* Check if the character is not BUF_FLUSH, then add it to the buffer */
    if (ch != BUFFER_FLUSH)
    {
        output_buffer[buffer_index++] = ch;
    }

    /* Return 1 on success */
    return 1;
}


/**
 * custom_write_to_fd - Writes a character to the specified file descriptor.
 * @ch: The character to be written.
 * @file_descriptor: The file descriptor to write to.
 *
 * This function writes the specified character to the given file descriptor.
 *
 * Return: On success, returns 1. On error, returns -1, and errno is set appropriately.
 */
int custom_write_to_fd(char ch, int file_descriptor)
{
    static int buffer_index;
    static char output_buffer[WRITE_BUFFER_SIZE];

    /* Use a while loop to continuously write characters to the buffer */
    while (1)
    {
        /* Check if it's time to flush the buffer or if the buffer is full */
        if (ch == BUFFER_FLUSH || buffer_index >= WRITE_BUFFER_SIZE)
        {
            /* Write the buffer to the specified file descriptor */
            write(file_descriptor, output_buffer, buffer_index);
            buffer_index = 0;
            break;
        }

        /* Check if the character is not BUF_FLUSH, then add it to the buffer */
        if (ch != BUFFER_FLUSH)
        {
            output_buffer[buffer_index++] = ch;
        }

        /* Return 1 on success */
        return 1;
    }

    /* On error, return -1 and set errno appropriately */
    return -1;
}


/**
 * custom_puts_to_fd - Prints an input string to the specified file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * This function prints the specified string to the given file descriptor.
 *
 * Return: The number of characters written.
 */
int custom_puts_to_fd(char *str, int fd)
{
    int char_count = 0;

    /* Check if the input string is NULL */
    if (!str)
        return 0;

    /* Use a while loop to iterate through the characters in the string */
    while (*str)
    {
        /* Increment the character count by the number of characters written to the file descriptor */
        char_count += custom_write_to_fd(*str++, fd);
    }

    /* Return the total number of characters written */
    return char_count;
}

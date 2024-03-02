#include "shell.h"

/**
 * _strcpy_custom - Copies a source string to a destination string
 * @dest: The destination string
 * @src: The source string to be copied
 *
 * Return: Pointer to the destination string
 */
char *_strcpy_custom(char *dest, char *src)
{
    int index = 0;

    /* If the destination is the same as the source or the source is NULL, return the destination */
    if (dest == src || src == NULL)
        return dest;

    /* Copy characters from source to destination */
    while (src[index])
    {
        dest[index] = src[index];
        index++;
    }

    /* Null-terminate the destination string */
    dest[index] = '\0';

    return dest;
}

/**
 * _strdup_custom - Duplicates a given string
 * @str: The string to duplicate
 *
 * Return: Pointer to the duplicated string
 */
char *_strdup_custom(const char *str)
{
    int length = 0;
    char *result;

    /* If the input string is NULL, return NULL */
    if (str == NULL)
        return NULL;

    /* Calculate the length of the input string */
    while (*str++)
        length++;

    /* Allocate memory for the duplicated string */
    result = malloc(sizeof(char) * (length + 1));

    /* If memory allocation fails, return NULL */
    if (!result)
        return NULL;

    /* Copy characters from the input string to the duplicated string*/
    for (length++; length--;)
        result[length] = *--str;

    return result;
}

/**
 * _puts_custom - Prints a string to the standard output
 * @str: The string to be printed
 *
 * Return: Nothing
 */
void _puts_custom(char *str)
{
    int index = 0;

    /* If the input string is NULL, do nothing */
    if (!str)
        return;

    /* Print characters from the string to the standard output */
    while (str[index] != '\0')
    {
        _putchar_custom(str[index]);
        index++;
    }
}

/**
 * _putchar_custom - Writes a character to the standard output
 * @c: The character to be written
 *
 * Return: On success, returns 1. On error, returns -1, and errno is set appropriately.
 */
int _putchar_custom(char c)
{
    static int index;
    static char buffer[WRITE_BUFFER_SIZE];

    /* If the character is a buffer flush indicator or the buffer is full, write the buffer to stdout */
    if (c == BUFFER_FLUSH|| index >= WRITE_BUFFER_SIZE)
    {
        write(1, buffer, index);
        index = 0;
    }

    /* If the character is not a buffer flush indicator, store it in the buffer */
    if (c != BUFFER_FLUSH)
        buffer[index++] = c;

    return 1;
}

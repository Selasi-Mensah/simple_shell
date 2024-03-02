#include "shell.h"

/**
 * _stringLength - Returns the length of a string
 * @str: The string whose length to determine
 *
 * Return: The integer length of the string
 */
int _stringLength(char *str)
{
    int length = 0;

    /* If the string is NULL, return 0 */
    if (!str)
        return 0;

    /*  Count the characters in the string */
    while (*str++)
        length++;

    return length;
}

/**
 * _stringCompare - Performs lexicographic comparison of two strings.
 * @str1: The first string
 * @str2: The second string
 *
 * Return: Negative if str1 < str2, positive if str1 > str2, zero if str1 == str2
 */
int _stringCompare(char *str1, char *str2)
{
    /* Compare characters until the end of one of the strings is reached */
    while (*str1 && *str2)
    {
        if (*str1 != *str2)
            return (*str1 - *str2);

        str1++;
        str2++;
    }

    /* If the characters match until the end of one string, compare string lengths */
    if (*str1 == *str2)
        return 0;
    else
        return (*str1 < *str2 ? -1 : 1);
}

/**
 * _startsWith - Checks if needle starts with haystack
 * @haystack: The string to search
 * @needle: The substring to find
 *
 * Return: Address of the next character of haystack or NULL if not found
 */
char *_startsWith(const char *haystack, const char *needle)
{
    /* Check if the substring matches the beginning of the string */
    while (*needle)
        if (*needle++ != *haystack++)
            return NULL;

    return (char *)haystack;
}

/**
 * _stringConcatenate - Concatenates two strings
 * @destination: The destination buffer
 * @source: The source buffer
 *
 * Return: Pointer to the destination buffer
 */
char *_stringConcatenate(char *destination, char *source)
{
    char *result = destination;

    /* Move to the end of the destination string */
    while (*destination)
        destination++;

    /* Copy characters from the source to the end of the destination*/
    while (*source)
        *destination++ = *source++;
    /* Ensure null-termination */
    *destination = *source;

    return result;
}

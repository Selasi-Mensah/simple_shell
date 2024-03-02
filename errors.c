#include "shell.h"

/**
 * custom_atoi - Converts a string to an integer.
 * @s: The string to be converted.
 * Return: 0 if no numbers in string, the converted number otherwise.
 *       -1 on error (including overflow or non-numeric characters).
 */
int custom_atoi(char *s)
{
    unsigned long int result = 0;

    /* If the first character is '+', skip it */
    if (*s == '+')
        s++;  /* TODO: Investigate the impact on main returning 255 */

    /* Process each character in the string using a while loop */
    while (*s != '\0')
    {
        /* Check if the character is a digit (0 to 9) */
        if (*s >= '0' && *s <= '9')
        {
            /* Update the result by multiplying it by 10 and adding the current digit */
            result *= 10;
            result += (*s - '0');

            /* Check for overflow */
            if (result > INT_MAX)
                return (-1);
        }
        else
        {
            /* Return -1 on encountering a non-numeric character */
            return (-1);
        }
        /* Move to the next character in the string */
        s++;
    }
    return (result);
}


/**
 * display_custom_error - Displays an error message.
 * @custom_info: The parameter & return custom_info struct.
 * @error_string: String containing the specified error type.
 *
 * This function prints an error message to standard error output.
 */
void display_custom_error(myInfoType *custom_info, char *error_string)
{
    custom_print_error_string(custom_info->file_name_str);
    custom_print_error_string(": ");
    print_custom_number(custom_info->count_line_flag, STDERR_FILENO);
    custom_print_error_string(": ");
    custom_print_error_string(custom_info->argument_array[0]);
    custom_print_error_string(": ");
    custom_print_error_string(error_string);
}


/**
 * print_custom_number - Prints a custom formatted number.
 * @input_number: The input number to be printed.
 * @output_fd: The file descriptor for output.
 *
 * Return: The number of characters printed.
 */
int print_custom_number(int input_number, int output_fd)
{
    /* Replace with your custom putchar function */
    int (*_putchar)(char) = _putchar;
    int i = 1000000000, character_count = 0;
    unsigned int absolute_value, current_digit;

    /*  Set _putchar to your putchar function if writing to custom output */
    if (output_fd == STDERR_FILENO)
        _putchar = custom_write_to_stderr;

    /*  Handle negative numbers */
    if (input_number < 0)
    {
        absolute_value = -input_number;
        _putchar('-');
        character_count++;
    }
    else
    {
        absolute_value = input_number;
    }

    current_digit = absolute_value;

    /* Loop through each digit in the number using a while loop */
    while (i > 1)
    {
        if (absolute_value / i)
        {
            /* Print the digit */
            _putchar('0' + current_digit / i);
            character_count++;
        }
        current_digit %= i;
        /* Update the divisor for the next digit */
        i /= 10;
    }
    /* Print the last digit */
    _putchar('0' + current_digit);
    character_count++;

    return character_count;
}


/**
 * custom_itoa - Custom integer to string converter.
 * @number: The number to be converted.
 * @base: The base for conversion (e.g., 10 for decimal).
 * @conversion_flags: Flags to control the conversion behavior.
 *
 * Return: String representation of the number.
 */
char *custom_itoa(long int number, int base, int conversion_flags)
{
    static char *digit_characters;
    static char result_buffer[50];
    char sign_indicator = 0;
    char *result_ptr;
    unsigned long absolute_value = (number < 0) ? -number : number;

    /*  Handle the sign for signed numbers */
    if (!(conversion_flags & CONVERT_UNSIGNED) && number < 0)
    {
        sign_indicator = '-';
    }

    /*  Define the character array for the conversion based on flags */
    digit_characters = (conversion_flags & CONVERT_LOWERCASE) ? "0123456789abcdef" : "0123456789ABCDEF";

    /*  Initialize the pointer to the result buffer */
    result_ptr = &result_buffer[49];
    *result_ptr = '\0';

    /*  Perform the conversion using a while loop */
    while (absolute_value != 0)
    {
        *--result_ptr = digit_characters[absolute_value % base];
        absolute_value /= base;
    }

    /*  Add the sign character if applicable */
    if (sign_indicator)
    {
        *--result_ptr = sign_indicator;
    }

    /*  Return the pointer to the resulting string */
    return result_ptr;
}


/**
 * custom_trim_comments - Replaces the first '#' with '\0' in a string.
 * @str: Address of the string to modify.
 *
 * This function replaces the first occurrence of '#' in the provided string
 * with the null terminator '\0'. The replacement is performed if '#' is either
 * the first character in the string or is preceded by a space.
 *
 * Return: Always 0.
 */
void custom_trim_comments(char *str)
{
    int index = 0;

    /*  Iterate through the characters in the string until null terminator is reached */
    while (str[index] != '\0')
    {
        /*  Check if the current character is '#' and if it is either the first character or the preceding character is a space */
        if (str[index] == '#' && (!index || str[index - 1] == ' '))
        {
            /*  Replace '#' with null terminator '\0' and break out of the loop */
            str[index] = '\0';
            break;
        }

        /*  Move to the next character in the string */
        index++;
    }
}
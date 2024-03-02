#include "shell.h"

/**
 * get_line - gets the input of a line
 * @custominfo: parameter struct
 * @buffer:
 * @len:
 *
 * Return: bytes read
 */
ssize_t get_line(myInfoType *custominfo, char **commands, size_t *length)
{
    ssize_t nread = 0;
    size_t n_pointer = 0;

    (void)custominfo;

    if (!*length)
    {
        free(*commands);
        *commands = NULL;
        signal(SIGINT, handle_signal);
#if USE_GETLINE
		nread = getline(commands, &n_pointer, stdin);
#else
		nread = _getline(custominfo, commands, &n_pointer);
#endif
        if (nread > 0)
        {
            if ((*commands)[nread - 1] == '\n')
            {
                (*commands)[nread - 1] = '\0';
                nread--;
            }
            custominfo->count_line_flag = 1;
			custom_trim_comments(*commands);
			bhistlist(custominfo, *commands, custominfo->history_line_count++);
            {
                *length = nread;
                custominfo->command_buffer_pointer = commands;
            }
        }
    }
    return (nread);
}


/**
 * get_commands - a function to get the commands
 * @custom_info - parameter struct
 * 
 * Return: bytes read
*/
ssize_t get_commands(myInfoType *custominfo)
{
    static char *commands;
    static size_t  a, b, length;
    ssize_t r = 0;
    char **buffer_pointer = &(custominfo->argument_string), *s;

    _putchar_custom(BUFFER_FLUSH);
    r = get_line(custominfo, &commands, &length);
    if (r == -1)
    {
        return (-1);
    }
    if (length)	/* we have commands left in the chain buffer */
	{
		b = a; /* init new iterator to current buf position */
		s = commands + a; /* get pointer for return */

		chainKeche(custominfo, commands, &b, a, length);
		while (b < length) /* iterate to semicolon or end */
		{
			if (chaining(custominfo, commands, &b))
				break;
			b++;
		}

		a = b + 1; /* increment past nulled ';'' */
		if (a >= length) /* reached end of buffer_pointerfer? */
		{
			a = length = 0; /* reset position and length */
			custominfo->command_buffer_type = NORMAL_COMMAND;
		}
        *buffer_pointer = s; /* pass back pointer to current command position */
		return (_stringLength(s)); /* return length of current command */
	}
    *buffer_pointer = commands;
    return (r);
}



/**
 * readCommands - reads a buffer
 * @custominfo: parameter struct
 * @commands: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t readCommands(myInfoType *custominfo, char *commands, size_t *p)
{
	ssize_t z = 0;

	if (*p)
		return (0);
	z = read(custominfo->read_file_descriptor, commands, READ_BUFFER_SIZE);
	if (z >= 0)
		*p = z;
	return (z);
}



/**
 * _getline - gets the next line of input from STDIN
 * @custominfo: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(myInfoType *custominfo, char **ptr, size_t *length)
{
	static char com[READ_BUFFER_SIZE];
	static size_t a, len;
	size_t v;
	ssize_t q = 0, t = 0;
	char *x = NULL, *pointer_new = NULL, *c;

	x = *ptr;
	if (x && length)
		t = *length;
	if (a == len)
		a = len = 0;

	q = readCommands(custominfo, com, &len);
	if (q == -1 || (q == 0 && len == 0))
		return (-1);

	c = _strchr(com + a, '\n');
	v = c ? 1 + (unsigned int)(c - com) : len;
	pointer_new = _realloc(x, t, t ? t + v : v + 1);
	if (!pointer_new) /* MALLOC FAILURE! */
		return (x ? free(x), -1 : -1);

	if (t)
		_strncat(pointer_new, com + a, v - a);
	else
		_strncpy(pointer_new, com + a, v - a + 1);

	t += v - a;
	a = v;
	x = pointer_new;

	if (length)
		*length = t;
	*ptr = x;
	return (t);
}


/**
 * handle_signal - ANSI C signal handling
 * @signum: signal integer
 * 
 * Return: Nothing
 *
*/
void handle_signal(__attribute__((unused))int signum)
{
    _puts_custom("\n");
    _puts_custom("$ ");
    _putchar_custom(BUFFER_FLUSH);
}


